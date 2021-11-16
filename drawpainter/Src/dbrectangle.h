#ifndef DBRECTANGLE_H
#define DBRECTANGLE_H
#include "dbvirtualgraph.h"
//四边形类
//鼠标划过矩形区域即为所画矩形
class dbrectangle:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbrectangle(QGraphicsItem *parent=NULL, int vertexNum=4);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void doPaint() override;
    enum { dbType = 3 };
    int dbtype() const;
};
#endif // DBRECTANGLE_H
