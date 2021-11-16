#include "dbellipse.h"
dbellipse::dbellipse(QGraphicsItem *parent,int vertexNum)
    :dbvirtualgraph(parent,vertexNum)
{
}

void dbellipse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbellipse::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverLeaveEvent(event);
}

void dbellipse::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::hoverMoveEvent(event);
    }
    else
    {

    }

}

void dbellipse::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverEnterEvent(event);
}
void dbellipse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
void dbellipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void dbellipse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
void dbellipse::doPaint()
{
    outlineLock.lock();
    outline.clear();
    outline=dbp.drawEllipse(QPoint((vertex[0].x()+vertex[1].x())/2,(vertex[0].y()+vertex[1].y())/2),
            std::abs(vertex[0].x()-vertex[1].x())/2,std::abs(vertex[0].y()-vertex[1].y())/2);

    outlineLock.unlock();
}
int dbellipse::dbtype() const
{
    return dbType;
}
