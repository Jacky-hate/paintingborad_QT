#include "dbbspline.h"
dbbspline::dbbspline(int vertexNum, int k, QGraphicsItem *parent)
    :dbvirtualgraph(parent,vertexNum,true),cur_vertexNum(0),controlv(vertexNum+k+1)
{
    for (int i=0;i<vertexNum;++i)
    {
        vertexhandler.push_back(new transformhandler(this,qRgb(0,255,255)));
        vertexhandler[i]->setVisible(false);
        connect(vertexhandler[i],&transformhandler::signalMove,this,&dbbspline::recvSetVertex);

    }
}
dbbspline:: ~dbbspline()
{
    for (int i=0;i<vertexhandler.size();++i)
    {
        delete vertexhandler[i];
    }
}
void dbbspline::boundingRectAlign()
{
    for (int i=0;i<cur_vertexNum;++i)
        vertexhandler[i]->setPos(vertex[i]);
    dbvirtualgraph::boundingRectAlign();
}

void dbbspline::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbbspline::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
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

void dbbspline::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
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

void dbbspline::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
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
void dbbspline::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
            dbvirtualgraph::mouseMoveEvent(event);
    }
    else
    {


    }
}
void dbbspline::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void dbbspline::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
void dbbspline::doPaint()
{
    int k=MIN(controlv.size()-vertex.size()-1,cur_vertexNum/2);
    if (!(stat&isFinished))
    {
        for (int i=0;i<cur_vertexNum-(k+1);++i)
        {
            controlv[i+k+1]=int(1000.0/(cur_vertexNum-(k+1)+1)*(i+1));
        }
        for (int i=0;i<k+1;++i)
        {
            controlv[i]=0;
        }
        for (int i=cur_vertexNum;i<k+cur_vertexNum+1;++i)
        {
            controlv[i]=1000;
        }
    }
    outlineLock.lock();
    outline.clear();
    std::vector<QPoint> v(vertex.begin(),vertex.begin()+cur_vertexNum);
    std::vector<int> c(controlv.begin(),controlv.begin()+cur_vertexNum+k+1);
    outline=dbp.drawBspline(v,c);
    outlineLock.unlock();
	/////////////////////////////
}
int dbbspline::dbtype() const
{
    return dbType;
}
void dbbspline::recvSetVertex(transformhandler *signalOwner, int x1, int y1, int x2, int y2)
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
void dbbspline::fill()
{

}
