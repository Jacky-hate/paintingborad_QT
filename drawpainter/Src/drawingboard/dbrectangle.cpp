#include "dbrectangle.h"
dbrectangle::dbrectangle(QGraphicsItem *parent,int vertexNum)
    :dbvirtualgraph(parent,vertexNum)
{
}

void dbrectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbrectangle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverLeaveEvent(event);
}

void dbrectangle::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverMoveEvent(event);
}

void dbrectangle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverEnterEvent(event);
}
void dbrectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
            dbvirtualgraph::mouseMoveEvent(event);
    }
    else
    {
        vertex[2]=event->scenePos().toPoint();
        vertex[1]=QPoint(vertex[2].x(),vertex[0].y());
        vertex[3]=QPoint(vertex[0].x(),vertex[2].y());
        doPaint();
    }
}
void dbrectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::mousePressEvent(event);
    }
    else
    {
       vertex[3]=vertex[2]=vertex[1]=vertex[0]=event->scenePos().toPoint();
        //stat&=~isFinished;
        setPos(0,0);
    }
}

void dbrectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
void dbrectangle::doPaint()
{


    outlineLock.lock();
    outline.clear();
    std::vector<QPoint> t;
    t=dbp.drawLine(vertex[0],vertex[1]);
    outline.insert(outline.end(),t.begin(),t.end());
    t=dbp.drawLine(vertex[1],vertex[2]);
    outline.insert(outline.end(),t.begin(),t.end());
    t=dbp.drawLine(vertex[2],vertex[3]);
    outline.insert(outline.end(),t.begin(),t.end());
    t=dbp.drawLine(vertex[3],vertex[0]);
    outline.insert(outline.end(),t.begin(),t.end());
    outlineLock.unlock();
}
int dbrectangle::dbtype() const
{
    return dbType;
}
