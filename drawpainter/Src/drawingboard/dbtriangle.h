#ifndef DBTRIANGLE_H
#define DBTRIANGLE_H
#include "dbvirtualgraph.h"
//三角形类
//鼠标划过矩形区域,下边为三角形底边,上边中点为三角形上顶点.
class dbtriangle:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbtriangle(QGraphicsItem *parent=NULL, int vertexNum=4);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void doPaint() override;
    enum { dbType = 8 };
    int dbtype() const;
};
#endif // DBTRIANGLE_H
