#include "dbline.h"
dbline::dbline(QGraphicsItem *parent,int vertexNum)
    :dbvirtualgraph(parent,vertexNum)
{
}

void dbline::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbline::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverLeaveEvent(event);
}

void dbline::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverMoveEvent(event);
}

void dbline::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverEnterEvent(event);
}
void dbline::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
            dbvirtualgraph::mouseMoveEvent(event);
    }
    else
    {
        vertex[1]=event->scenePos().toPoint();
        doPaint();
    }
}
void dbline::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::mousePressEvent(event);
    }
    else
    {
        vertex[1]=vertex[0]=event->scenePos().toPoint();
        //stat&=~isFinished;
        setPos(0,0);
    }
}

void dbline::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::mouseReleaseEvent(event);

    }
    else
    {
        vertex[1]=event->scenePos().toPoint();
        stat|=isFinished;
        positionChanged();
    }
}
void dbline::doPaint()
{
    outlineLock.lock();
    outline.clear();
    outline=dbp.drawLine(vertex[0],vertex[1]);
    outlineLock.unlock();
}
int dbline::dbtype() const
{
    return dbType;
}
void dbline::fill()
{

}
