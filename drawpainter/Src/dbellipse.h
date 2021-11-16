#ifndef DBELLIPSE_H
#define DBELLIPSE_H
#include "dbvirtualgraph.h"
//椭圆类
//鼠标划过矩形区域,中心作圆心,矩形长宽构成两个椭圆参数
class dbellipse:public dbvirtualgraph
{
    Q_OBJECT
public:
    dbellipse(QGraphicsItem *parent=NULL, int vertexNum=2);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void doPaint() override;
    enum { dbType = 5 };
    int dbtype() const;
};

#endif // DBELLIPSE_H
