#ifndef dbbezierfitFIT_H
#define dbbezierfitFIT_H
#include "dbvirtualgraph.h"
//曲线拟合点集类
//用分段三阶贝塞尔曲线相连做拟合,待拟合点前后的控制点由前驱和后继待拟合点决定,使得分段贝塞尔曲线连接处斜率一致,保证平滑
class dbbezierfit:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbbezierfit(int vertexNum,QGraphicsItem *parent=NULL);
    ~dbbezierfit();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void boundingRectAlign();
    void doPaint() override;
    void fill();
    enum { dbType = 5 };
    int dbtype() const;
    int cur_vertexNum;
    std::vector<transformhandler*> vertexhandler;
public slots:
    void recvSetVertex(transformhandler *signalOwner, int x1, int y1, int x2, int y2);
};
#endif // dbbezierfitFIT_H
