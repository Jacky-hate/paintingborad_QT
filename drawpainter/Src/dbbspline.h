#ifndef DBBSPLINE_H
#define DBBSPLINE_H
#include "dbvirtualgraph.h"
//B-spline类
//指定控制点集大小vertexNum,以及次数k,鼠标依次指定各控制点位置,以当前点个数为阶数即时作图
//前后k+1个分段节点与首尾控制点重合,以保证实际曲线开始于第一个控制点,结束于最后一个控制点
class dbbspline:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbbspline(int vertexNum,int k=2,QGraphicsItem *parent=NULL);
    ~dbbspline();
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
    enum { dbType = 6 };
    int dbtype() const;
    int cur_vertexNum;
    std::vector<transformhandler*> vertexhandler;
    std::vector<int> controlv;
public slots:
    void recvSetVertex(transformhandler *signalOwner, int x1, int y1, int x2, int y2);
};
#endif // DBBSPLINE_H
