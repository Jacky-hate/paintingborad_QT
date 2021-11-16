#include "transformhandler.h"
#include <QColor>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
transformhandler::transformhandler(QGraphicsItem *parentItem,QColor c, QObject *parent)
    :QObject(parent),_b(QBrush(c))
{
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
    setBrush(_b);
    setRect(-4,-4,8,8);
}
void transformhandler::setPreviousPosition(const QPointF &pos)
{
    if (previousPosition == pos)
        return;

    previousPosition = pos;
}


void transformhandler::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    int x1=previousPosition.x(),y1=previousPosition.y(),x2=event->scenePos().x(),y2=event->scenePos().y();
    auto dx = event->scenePos().x() - previousPosition.x();
    auto dy = event->scenePos().y() - previousPosition.y();
    moveBy(dx,dy);
    setPreviousPosition(event->scenePos());
    emit signalMove(this,x1,y1,x2,y2);
}

void transformhandler::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setPreviousPosition(event->scenePos());
    emit signalMousePress();
}

void transformhandler::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalMouseRelease();
}

void transformhandler::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::red));
}

void transformhandler::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(_b);
}
