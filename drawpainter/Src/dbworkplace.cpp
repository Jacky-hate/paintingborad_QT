#include "dbworkplace.h"
#include "dbline.h"
#include "dbrectangle.h"
#include "dbpolygon.h"
#include "dbbezier.h"
#include "dbellipse.h"
#include "dbbspline.h"
#include "dbtriangle.h"
#include "dbcircle.h"
#include "dbbezierfit.h"
#include <QDebug>
#include <QList>

dbworkplace::dbworkplace(QObject *parent)
    :QGraphicsScene(parent),mode(SELECTING),currentItem(NULL),isdrawing(false),isLeftButtonPressed(false),
      fillc(qRgb(255,255,0)),outlinec(qRgb(0,0,0)),linewidth(1),bezierVertexNum(4),bsplineVertexNum(6),
      bsplineVertexk(3),bezierFitVertexNum(4)
{
    mode=LINE;

    //connect()
}

void dbworkplace::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pend=pbeg=event->scenePos().toPoint();
    if (event->button() & Qt::LeftButton)
        isLeftButtonPressed=true;
    switch (mode)
    {
    case LINE:
    {

        currentItem=new dbline();
        setPen(currentItem);
        dbline * _line = dbvirtualgraph::dbgraphicsitem_cast<dbline *>(currentItem);
        addItem(currentItem);
        connect(_line,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
        //qDebug()<<items().size();
        break;
    }
    case TRIANGLE:
    {
        currentItem=new dbtriangle();
        setPen(currentItem);
        dbtriangle * _tri = dbvirtualgraph::dbgraphicsitem_cast<dbtriangle *>(currentItem);
        if (_tri)
        {
            connect(_tri,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
            addItem(currentItem);
        }

        break;
    }
    case RECTANGLE:
    {
        currentItem=new dbrectangle();
        setPen(currentItem);
        dbrectangle * _rect = dbvirtualgraph::dbgraphicsitem_cast<dbrectangle *>(currentItem);
        if (_rect)
        {
            connect(_rect,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
            addItem(currentItem);
        }

        break;
    }
    case POLYGON:
    {
        if (!currentItem||currentItem->stat&dbvirtualgraph::isFinished)
        {
            currentItem=new dbpolygon();
            setPen(currentItem);
            dbpolygon * _poly = dbvirtualgraph::dbgraphicsitem_cast<dbpolygon *>(currentItem);
            if (_poly)
            {
                connect(_poly,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
                addItem(currentItem);
            }
        }


        break;
    }
    case ELLIPSE:
    {
        currentItem=new dbellipse();
        setPen(currentItem);
        dbellipse * _elip = dbvirtualgraph::dbgraphicsitem_cast<dbellipse *>(currentItem);
        if (_elip)
        {
            connect(_elip,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
            addItem(currentItem);
        }

        break;
    }
    case CIRCLE:
    {
        currentItem=new dbcircle();
        setPen(currentItem);
        dbcircle * _cir = dbvirtualgraph::dbgraphicsitem_cast<dbcircle *>(currentItem);
        if (_cir)
        {
            connect(_cir,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
            addItem(currentItem);
        }

        break;
    }
    case BEZIER:
    {
        if (!currentItem||currentItem->stat&dbvirtualgraph::isFinished)
        {
            currentItem=new dbbezier(bezierVertexNum);
            setPen(currentItem);
            dbbezier * _bezi = dbvirtualgraph::dbgraphicsitem_cast<dbbezier *>(currentItem);
            if (_bezi)
            {
                connect(_bezi,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
                addItem(currentItem);
            }
        }


        break;
    }
    case BSPLINE:
    {
        if (!currentItem||currentItem->stat&dbvirtualgraph::isFinished)
        {
            currentItem=new dbbspline(bsplineVertexNum,bsplineVertexk);
            setPen(currentItem);
            dbbspline * _bsp = dbvirtualgraph::dbgraphicsitem_cast<dbbspline *>(currentItem);
            if (_bsp)
            {
                connect(_bsp,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
                addItem(currentItem);
            }
        }


        break;
    }
    case FIT_B:
    {
        if (!currentItem||currentItem->stat&dbvirtualgraph::isFinished)
        {
            currentItem=new dbbezierfit(bezierFitVertexNum);
            setPen(currentItem);
            dbbezierfit * _bzf = dbvirtualgraph::dbgraphicsitem_cast<dbbezierfit *>(currentItem);
            if (_bzf)
            {
                connect(_bzf,&dbvirtualgraph::selected,this,&dbworkplace::recvSelect);
                addItem(currentItem);
            }
        }
        break;
    }
    case SELECTING:
    {
        break;
    }

    }
    QGraphicsScene::mousePressEvent(event);
}
void dbworkplace::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    pend=event->scenePos().toPoint();
    //qDebug()<<pend<<"\n";
    switch (mode)
    {
    case LINE:
    {
        dbline * _line = dbvirtualgraph::dbgraphicsitem_cast<dbline *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();

        break;
    }
    case TRIANGLE:
    {
        dbtriangle * _tri = dbvirtualgraph::dbgraphicsitem_cast<dbtriangle *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();

        break;
    }
    case RECTANGLE:
    {
        dbrectangle * rect = dbvirtualgraph::dbgraphicsitem_cast<dbrectangle *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();
        break;
    }
    case POLYGON:
    {
        dbpolygon * _poly = dbvirtualgraph::dbgraphicsitem_cast<dbpolygon *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();

        break;
    }
    case ELLIPSE:
    {
        dbellipse * _elip = dbvirtualgraph::dbgraphicsitem_cast<dbellipse *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();

        break;
    }
    case CIRCLE:
    {
        dbcircle * _cir = dbvirtualgraph::dbgraphicsitem_cast<dbcircle *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();
        break;
    }
    case BEZIER:
    {
        dbbezier * _bezi = dbvirtualgraph::dbgraphicsitem_cast<dbbezier *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();
        break;
    }
    case BSPLINE:
    {
        dbbspline * _bsp = dbvirtualgraph::dbgraphicsitem_cast<dbbspline *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();
        break;
    }
    case FIT_B:
    {
        dbbezierfit * _bzf = dbvirtualgraph::dbgraphicsitem_cast<dbbezierfit *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        update();
        break;
    }
    case SELECTING:
    {
        if (isLeftButtonPressed)
        {
        }

        break;
    }
    }
    QGraphicsScene::mouseMoveEvent(event);
}
void dbworkplace::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pend=event->scenePos().toPoint();
    if (event->button() & Qt::LeftButton)
        isLeftButtonPressed = false;
    switch (mode)
    {
    case LINE:
    {
        dbline * _line = dbvirtualgraph::dbgraphicsitem_cast<dbline *>(currentItem);

        break;
    }
    case TRIANGLE:
    {
        dbtriangle * _tri = dbvirtualgraph::dbgraphicsitem_cast<dbtriangle *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        break;
    }
    case RECTANGLE:
    {
        dbrectangle * _rect = dbvirtualgraph::dbgraphicsitem_cast<dbrectangle *>(currentItem);
        break;
    }
    case POLYGON:
    {
        dbpolygon * _poly = dbvirtualgraph::dbgraphicsitem_cast<dbpolygon *>(currentItem);
        if (isLeftButtonPressed)
        {

        }

        break;
    }
    case ELLIPSE:
    {
        dbellipse * _elip = dbvirtualgraph::dbgraphicsitem_cast<dbellipse *>(currentItem);
        if (isLeftButtonPressed)
        {

        }

        break;
    }
    case CIRCLE:
    {
        dbcircle * _cir = dbvirtualgraph::dbgraphicsitem_cast<dbcircle *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        break;
    }
    case BEZIER:
    {
        dbbezier * _bezi = dbvirtualgraph::dbgraphicsitem_cast<dbbezier *>(currentItem);
        if (isLeftButtonPressed)
        {

        }


        break;
    }
    case BSPLINE:
    {
        dbbspline * _bsp = dbvirtualgraph::dbgraphicsitem_cast<dbbspline *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        break;
    }
    case FIT_B:
    {
        dbbezierfit * _bzf = dbvirtualgraph::dbgraphicsitem_cast<dbbezierfit *>(currentItem);
        if (isLeftButtonPressed)
        {

        }
        break;
    }
    case SELECTING:
    {
        break;
    }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
void dbworkplace::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
void dbworkplace::keyPressEvent(QKeyEvent *event)
{

}
void dbworkplace::selectionMode(objType mode)
{
    this->mode=mode;
    QList<QGraphicsItem*> all = items();
    for (int i = 0; i < all.size(); i++)
    {
        QGraphicsItem *gi = all[i];
        dbvirtualgraph * _graph = qgraphicsitem_cast<dbvirtualgraph *>(gi);
        if (_graph)
            _graph->stat|=dbvirtualgraph::isActive;
    }
}

void dbworkplace::drawMode(objType mode)
{
    this->mode=mode;
    QList<QGraphicsItem*> all = items();
    for (int i = 0; i < all.size(); i++)
    {
        QGraphicsItem *gi = all[i];
        dbvirtualgraph * _graph = qgraphicsitem_cast<dbvirtualgraph *>(gi);
        if (_graph)
        {
            _graph->stat&=~(dbvirtualgraph::isActive);
            _graph->stat&=~(dbvirtualgraph::isSelected);
            _graph->deHovering();
        }
    }
    currentItem=NULL;
}

void dbworkplace::clearALL()
{
    this->clear();
    currentItem=NULL;
}
void dbworkplace::fillItem()
{
    dbvirtualgraph * vg = dbvirtualgraph::dbgraphicsitem_cast<dbvirtualgraph *>(currentItem);
    if (vg)
        vg->fill();
}
void dbworkplace::defillItem()
{
    dbvirtualgraph * vg = dbvirtualgraph::dbgraphicsitem_cast<dbvirtualgraph *>(currentItem);
    if (vg)
        vg->defill();
}

void dbworkplace::recvSelect(dbvirtualgraph *item)
{
    currentItem=item;
    if (mode!=MULTISELECT)
    {
        QList<QGraphicsItem*> all = items();

        for (int i = 0; i < all.size(); i++)
        {
            QGraphicsItem *gi = all[i];
            dbvirtualgraph * _graph = qgraphicsitem_cast<dbvirtualgraph *>(gi);
            if (_graph)
            {
                _graph->stat&=~(dbvirtualgraph::isSelected);
                _graph->deHovering();
            }

        }
    }
    item->stat|=dbvirtualgraph::isSelected;
    item->doHovering();
}
void dbworkplace::setLineWid(const QString &s)
{
    this->linewidth=s.toInt();

}

void dbworkplace::setColor(QColor outlinec,QColor fillc)
{
    this->outlinec=outlinec;
    this->fillc=fillc;
    if (currentItem)
        currentItem->setFillColor(fillc);
}
void dbworkplace::deleteItem()
{
    QList<QGraphicsItem*> all = items();

    for (int i = 0; i < all.size(); i++)
    {
        QGraphicsItem *gi = all[i];
        dbvirtualgraph * _graph = qgraphicsitem_cast<dbvirtualgraph *>(gi);
        if (_graph&&_graph->stat&dbvirtualgraph::isSelected)
        {
            gi->setVisible(false);
            //removeItem(gi);
            //delete gi;
        }
    }
    currentItem=NULL;
}
void dbworkplace::setbezierVertexNum(const QString &s)
{
    bezierVertexNum=s.toInt();
}
void dbworkplace::setbsplineVertexNum(const QString &s)
{
    bsplineVertexNum=s.toInt();
}
void dbworkplace::setbsplineVertexk(const QString &s)
{
    bsplineVertexk=s.toInt();
}
void dbworkplace::setLineType(const QString &s)
{
    if (s=="SOLIDE")
        _type=dbpainter::SOLIDE;
    else if (s=="DOT")
            _type=dbpainter::DOTTED;
    else if (s=="DASHED")
        _type=dbpainter::DASHED;
}
void dbworkplace::setPen(dbvirtualgraph *item)
{
    item->setPenWid(linewidth);
    item->setFillColor(fillc);
    item->setColor(outlinec);
    item->setPenType(_type);
}
void dbworkplace::setbezierFitVertexNum(const QString &s)
{
    bezierFitVertexNum=s.toInt();
}
