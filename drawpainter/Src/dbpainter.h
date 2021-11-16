#ifndef DBPAINTER_H
#define DBPAINTER_H
#include<QPainter>
#define MIN(a,b) a<b?(a):(b)
#define MAX(a,b) a>b?(a):(b)
//绘图类,集成图形算法和填充算法
class dbpainter
{
public:
    enum linetype{SOLIDE,DOTTED,DASHED};
    dbpainter();
    //width*width区域内的点
    std::vector<QPoint> drawPoint(const QPoint &p);
    //Bresenham算法
    std::vector<QPoint> drawLine(const QPoint &p1, const QPoint &p2);
    //中点算法
    std::vector<QPoint> drawEllipse(const QPoint &center, int Rx, int Ry);
    //de castejau算法
    std::vector<QPoint> drawBezier(std::vector<QPoint> &vertex,const int outlineNum=1000);
    //基函数为Cox-deBoor递推公式
    std::vector<QPoint> drawBspline(std::vector<QPoint> &vertex, std::vector<int> &controlv);
    //分段三阶贝塞尔曲线的拼接
    std::vector<QPoint> drawBezierFit(std::vector<QPoint> &vertex);

    //以一定间隔过滤轮廓,构造不同线条类型
    std::vector<QPoint> handleOutline(std::vector<QPoint> &outline);

    //凸性形状简单填充
    std::vector<QPoint> fill(std::vector<QPoint> &outline,int lowx,int lowy,int highx,int highy);
    //多边形扫描线填充算法
    std::vector<QPoint> polygonfill(std::vector<QPoint> &pointv,int lowx,int lowy,int highx,int highy);

    void setPenWid(int wid);
    void setPenType(dbpainter::linetype type);
protected:
    void insertV(std::vector<QPoint> &pointv, QPoint p);
    void getControlPoint(const QPoint &pt, const QPoint &p1, const QPoint &p2,
                                       QPoint &control1, QPoint &control2, double ratio);
    linetype type;
    int width;
};

#endif // DBPAINTER_H
