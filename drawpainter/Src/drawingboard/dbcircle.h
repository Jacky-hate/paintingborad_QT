#ifndef DBCIRCLE_H
#define DBCIRCLE_H
#include "dbvirtualgraph.h"
//圆类
//鼠标划过矩形区域,左上角坐标作圆心,与右下角的距离作圆半径
class dbcircle:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbcircle(QGraphicsItem *parent=NULL, int vertexNum=2);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void doPaint() override;
    enum { dbType = 7 };
    int dbtype() const;
};
#endif // DBCIRCLE_H
