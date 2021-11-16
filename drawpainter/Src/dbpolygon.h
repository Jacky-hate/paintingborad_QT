#ifndef DBPOLYGON_H
#define DBPOLYGON_H
#include "dbvirtualgraph.h"
//多边形类
//非预先设置定点数;由多段直线构成,最后一段直线结尾点与第一段直线始点距离小于20px时会相连,此时停止可结束绘制；
class dbpolygon:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbpolygon(QGraphicsItem *parent=NULL, int vertexNum=1);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void doPaint() override;
    enum { dbType = 4 };
    int dbtype() const;
};
#endif // DBPOLYGON_H
