#include "dbcircle.h"
dbcircle::dbcircle(QGraphicsItem *parent,int vertexNum)
    :dbvirtualgraph(parent,vertexNum)
{
}

void dbcircle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbcircle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverLeaveEvent(event);
}

void dbcircle::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::hoverMoveEvent(event);
    }
    else
    {

    }

}

void dbcircle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverEnterEvent(event);
}
void dbcircle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
void dbcircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void dbcircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::mouseReleaseEvent(event);

    }
    else
    {
        stat|=isFinished;
        positionChanged();
    }
}
void dbcircle::doPaint()
{
    outlineLock.lock();
    outline.clear();
    outline=dbp.drawEllipse(vertex[0],getDis(vertex[0],vertex[1]),getDis(vertex[0],vertex[1]));

    outlineLock.unlock();
}
int dbcircle::dbtype() const
{
    return dbType;
}
