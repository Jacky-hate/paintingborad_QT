#ifndef DBLINE_H
#define DBLINE_H
#include "dbvirtualgraph.h"
//直线类
//鼠标划过矩形区域,左上到右下对角线即为所画直线
class dbline: public dbvirtualgraph
{
    Q_OBJECT
public:
    dbline(QGraphicsItem *parent=NULL, int vertexNum=2);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void doPaint() override;
    void fill();
    enum { dbType = 2 };
    int dbtype() const;
};

#endif // DBLINE_H
