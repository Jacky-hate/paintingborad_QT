#include "dbbezier.h"
dbbezier::dbbezier(int vertexNum, QGraphicsItem *parent)
    :dbvirtualgraph(parent,vertexNum,true),cur_vertexNum(0)
{
    for (int i=0;i<vertexNum;++i)
    {
        vertexhandler.push_back(new transformhandler(this,qRgb(0,255,255)));
        vertexhandler[i]->setVisible(false);
        connect(vertexhandler[i],&transformhandler::signalMove,this,&dbbezier::recvSetVertex);
    }

}
dbbezier:: ~dbbezier()
{
    for (int i=0;i<vertexhandler.size();++i)
        delete vertexhandler[i];
}
void dbbezier::boundingRectAlign()
{
    for (int i=0;i<cur_vertexNum;++i)
        vertexhandler[i]->setPos(vertex[i]);
    dbvirtualgraph::boundingRectAlign();
}

void dbbezier::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbbezier::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            if (!(stat&isSelected))
                for (auto &it:vertexhandler)
                    it->setVisible(false);

        }
    }
    dbvirtualgraph::hoverLeaveEvent(event);
}

void dbbezier::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::hoverMoveEvent(event);
    }
    else if (stat&isDrawing)
    {
        QPoint p=event->scenePos().toPoint();
        vertex[cur_vertexNum-1]=p;
        doPaint();
        positionChanged();
    }

}

void dbbezier::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            for (auto &it:vertexhandler)
                it->setVisible(true);

        }
    }
    dbvirtualgraph::hoverEnterEvent(event);
}
void dbbezier::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
            dbvirtualgraph::mouseMoveEvent(event);
    }
    else
    {


    }
}
void dbbezier::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            if (cur_vertexNum==vertex.size())
            {
                stat&=~isDrawing;
                saved_v=vertex;
                stat|=isFinished;
                vertexhandler[cur_vertexNum-1]->setVisible(true);
                positionChanged();
            }
            else
            {
                vertexhandler[cur_vertexNum-1]->setVisible(true);
            }
        }
        else
        {
            vertex[0]=event->scenePos().toPoint();
            vertexhandler[cur_vertexNum]->setVisible(true);
            cur_vertexNum++;
            stat|=isDrawing;
            setPos(0,0);
        }
    }
}

void dbbezier::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        dbvirtualgraph::mouseReleaseEvent(event);

    }
    else
    {

        if (stat&isDrawing)
        {

            cur_vertexNum++;
        }
        else
        {

        }
    }
}
void dbbezier::doPaint()
{
    outlineLock.lock();
    outline.clear();
    std::vector<QPoint> t(vertex.begin(),vertex.begin()+cur_vertexNum);
    outline=dbp.drawBezier(t);
    outlineLock.unlock();
}
int dbbezier::dbtype() const
{
    return dbType;
}
void dbbezier::recvSetVertex(transformhandler *signalOwner, int x1, int y1, int x2, int y2)
{
    int i=0;
    for (i=0;i<vertexhandler.size();++i)
        if (vertexhandler[i]==signalOwner)
        {
            vertex[i]=QPoint(x2,y2);
            doPaint();
            positionChanged();
            break;
        }
}
void dbbezier::fill()
{

}
