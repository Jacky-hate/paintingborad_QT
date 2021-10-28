#ifndef DBBEZIER_H
#define DBBEZIER_H
#include "dbvirtualgraph.h"
//贝塞尔曲线类
//指定点集大小vertexNum,鼠标依次指定各控制点位置,以当前点个数为阶数即时作图
class dbbezier:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbbezier(int vertexNum,QGraphicsItem *parent=NULL);
    ~dbbezier();
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
#endif // DBBEZIER_H
