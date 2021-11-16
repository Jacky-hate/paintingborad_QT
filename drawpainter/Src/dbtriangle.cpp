#include "dbtriangle.h"
dbtriangle::dbtriangle(QGraphicsItem *parent,int vertexNum)
    :dbvirtualgraph(parent,vertexNum)
{
}

void dbtriangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbtriangle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverLeaveEvent(event);
}

void dbtriangle::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverMoveEvent(event);
}

void dbtriangle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverEnterEvent(event);
}
void dbtriangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
void dbtriangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void dbtriangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
void dbtriangle::doPaint()
{
    QPoint top((vertex[0].x()+vertex[1].x())/2,(vertex[0].y()+vertex[1].y())/2);
    outlineLock.lock();
    outline.clear();
    std::vector<QPoint> t;
    t=dbp.drawLine(top,vertex[2]);
    outline.insert(outline.end(),t.begin(),t.end());
    t=dbp.drawLine(vertex[2],vertex[3]);
    outline.insert(outline.end(),t.begin(),t.end());
    t=dbp.drawLine(vertex[3],top);
    outline.insert(outline.end(),t.begin(),t.end());
    outlineLock.unlock();
}
int dbtriangle::dbtype() const
{
    return dbType;
}
