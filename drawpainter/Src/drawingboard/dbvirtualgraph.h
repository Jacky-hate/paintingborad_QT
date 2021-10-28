#ifndef DBVIRTUALGRAPH_H
#define DBVIRTUALGRAPH_H

#include <QGraphicsItem>
#include <vector>
#include "dbpainter.h"
#include "transformhandler.h"
#include <QGraphicsSceneMouseEvent>
#include <mutex>
#include <type_traits>
#include <QDebug>
#include <set>
#include <QCursor>
#include <algorithm>
#include <math.h>
#define MIN(a,b) a<b?(a):(b)
#define MAX(a,b) a>b?(a):(b)
#define pai (3.1415926535897932384626)
//矢量图虚类:

//以矩形框作为碰撞检测域和鼠标响应域
//根据不同形状自定义鼠标响应和悬浮事件，用于在鼠标移动过程中保存需要的顶点集vertex
//dbpainter集成绘制算法，dopaint函数使用dbpainter根据顶点集生成轮廓集outline
//transformhandler类作为一个变换操作的按钮，tfhand_v中有八个用于缩放，位于四角与角间中点;rotateHandler,centerHandler用于旋转
//平移旋转和放缩变换操作于顶点集，并调用dopaint函数重绘顶点集
//变换操作需要调用positionChanged以对其各个按钮(handler)，以及生成新的边缘矩形等
//填充fill操作于轮廓集，并保存为填充集fillv
//场景显示时，自动调用各形状的paint函数以绘制最终视图，paint函数绘制保存的轮廓集和填充集
class dbvirtualgraph: public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
#define PADSIZE 30  //边距
    dbvirtualgraph(QGraphicsItem *parent, int vertexNum, bool unconvex=false);
    //禁用拷贝
    dbvirtualgraph(const dbvirtualgraph&) = delete;
    dbvirtualgraph& operator=(const dbvirtualgraph&) = delete;
    virtual ~dbvirtualgraph();
    //边界及碰撞域函数
    virtual QRectF boundingRect()const;
    //场景绘制时自动调用
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    //设置轮廓颜色
    void setColor(QColor &c);
    //设置填充颜色
    void setFillColor(QColor &c);
    //设置轮廓宽度
    void setPenWid(int wid);
    //设置画笔类型
    void setPenType(dbpainter::linetype type);

    //鼠标移动
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    //鼠标按下
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //鼠标释放
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //鼠标双击
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    //悬浮表示无按键按下
    //鼠标悬浮离开
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    //鼠标悬浮移动
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    //鼠标悬浮进入
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    //主动绘制函数,通过顶点绘制图像
    virtual void doPaint()=0;


    //变换操作,考虑到是矢量图，变换的对象是顶点集
    //旋转
    virtual void rotate(double theta,QPoint center=QPoint(0,0));
    //放大,放大至矩形边界左上角为topleft,右下角为lowerright
    virtual void zoom(QPoint topleft, QPoint lowerright);
    //移动
    virtual void move(int dx,int dy);

    //形状或位置改变时调用,对其变换按钮等
    virtual void positionChanged();

    //鼠标悬停进入时调用
    void doHovering();
    //鼠标悬停离开时调用
    void deHovering();

    //状态类型
    //isFinished:图形绘制是否结束
    //isActive:是否处于SELECTING模式
    //isSelected:是否被选中
    //isRotating:是否正在旋转
    //isRotating:是否被填充
    //isDrawing:是否正在绘制
    enum status{
        isFinished=0x01,
        isActive=0x02,
        isSelected=0x04,
        isRotating=0x08,
        isFilled=0x10,
        isDrawing=0x20,
        unConvex=0x40,
    };
    //状态值
    int stat;

    //对不同方向拉伸时内部调用,对其按钮(句柄)
    void resizeTop(int i,int dx,int dy);
    void resizeButtom(int i,int dx,int dy);
    void resizeLeft(int i,int dx,int dy);
    void resizeRight(int i,int dx,int dy);

    //保存顶点状态
    void save();
    //恢复顶点状态
    void restore();

    //填充函数
    virtual void fill();
    //取消填充函数
    void defill();

    enum { Type = UserType + 1 };
    //用于QGraphicsItem类型识别
    int type() const override;

    enum { dbType = 1 };
    //用于本类及子类类型识别
    virtual int dbtype() const=0;
    //用于本类及子类类型转换
    template <class T> T static dbgraphicsitem_cast(dbvirtualgraph *item)
    {
        typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
        return int(Item::dbType) == int(dbvirtualgraph::dbType)
            || (item && int(Item::dbType) == item->dbtype()) ? static_cast<T>(item) : 0;
    }
    //两点距离函数
    double static getDis(const QPoint &p1, const QPoint &p2);

    //放缩变换句柄(按钮),分布于八个角落
    std::vector<transformhandler*> tfhand_v;
    //旋转变换句柄(按钮),旋转句柄和中心
    transformhandler *rotateHandler,*centerHandler;
protected:
    //内部变换函数，实现顶点变换而不重绘
    void doMove(int dx,int dy);
    void doRotate(double theta, QPoint center=QPoint(0,0));
    void doZoom(QPoint topleft, QPoint lowerright);
    //对齐放缩变换句柄
    virtual void transformhandlerAlign();
    //对齐旋转句柄
    virtual void rotatehandlerAlign();
    //对齐边界矩形
    virtual void boundingRectAlign();

    //顶点数组
    std::vector<QPoint> vertex;
    //填充数组
    std::vector<QPoint> fillv;
    //旋转始点
    QPoint rotateStart;
    //保存的顶点数组
    std::vector<QPoint> saved_v;
    //轮廓色
    QColor c;
    //填充色
    QColor fillc;
    //线条类型
    dbpainter::linetype _linetype;


    //边界矩阵的左上右下坐标值
    int lowx,lowy,highx,highy;
    //保存的边界矩阵的左上右下坐标值
    int savedlowx,savedlowy,savedhighx,savedhighy;
    //轮廓坐标数组
    std::vector<QPoint> outline;
    //画笔类型加工后的轮廓
    std::vector<QPoint> displayedOutline;

    //轮廓数组互斥锁,避免在绘制过程中修改
    std::mutex outlineLock;
    //自定义绘制类
    dbpainter dbp;
    //上一个位置,用于鼠标移动记录
    QPoint lastPosition;


signals:
    //选择信号
    void selected(dbvirtualgraph *item);
public slots:
    //接收缩放变换句柄的移动
    void recvMove(transformhandler *signalOwner,int x1,int y1,int x2,int y2);
    //接收旋转变换句柄的旋转
    void recvRotate(transformhandler *signalOwner, int x1, int y1, int x2, int y2);
    //旋转开始
    void rotateBeg();
    //旋转结束
    void rotateEnd();
    //移动状态改变
    void moveStatChanged();
};

#endif // DBVIRTUALGRAPH_H
