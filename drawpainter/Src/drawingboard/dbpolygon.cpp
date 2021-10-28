#include "dbpolygon.h"
dbpolygon::dbpolygon(QGraphicsItem *parent,int vertexNum)
    :dbvirtualgraph(parent,vertexNum,true)
{
}

void dbpolygon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbpolygon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverLeaveEvent(event);
}

void dbpolygon::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::hoverMoveEvent(event);
    }
    else if (stat&isDrawing)
    {
        QPoint p=event->scenePos().toPoint();
        int size=vertex.size();
        if (getDis(p,vertex[0])<20)
        {
            vertex[size-1]=vertex[0];
        }
        else
            vertex[size-1]=p;
        doPaint();
        positionChanged();
    }

}

void dbpolygon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    dbvirtualgraph::hoverEnterEvent(event);
}
void dbpolygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
            dbvirtualgraph::mouseMoveEvent(event);
    }
    else
    {


    }
}
void dbpolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::mousePressEvent(event);
    }
    else
    {
        if (stat&isDrawing)
        {
            QPoint p=event->scenePos().toPoint();
            if (getDis(p,vertex[0])<20)
            {
                stat&=~isDrawing;
                saved_v=vertex;
                stat|=isFinished;
                positionChanged();
            }
            else
            {

            }
        }
        else
        {
            vertex[0]=event->scenePos().toPoint();
            stat|=isDrawing;
            setPos(0,0);
        }
    }
}

void dbpolygon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::mouseReleaseEvent(event);

    }
    else
    {
        if (stat&isDrawing)
        {
            vertex.push_back(QPoint(0,0));
        }
        else
        {

        }
    }
}
void dbpolygon::doPaint()
{
    outlineLock.lock();
    outline.clear();
    std::vector<QPoint> t;
    for (int i=0;i<vertex.size()-1;++i)
    {
        t=dbp.drawLine(vertex[i],vertex[i+1]);
        outline.insert(outline.end(),t.begin(),t.end());
    }
    outlineLock.unlock();
}
int dbpolygon::dbtype() const
{
    return dbType;
}
