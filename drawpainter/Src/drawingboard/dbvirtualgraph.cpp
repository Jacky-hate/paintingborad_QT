#include "dbvirtualgraph.h"

dbvirtualgraph::dbvirtualgraph(QGraphicsItem *parent, int vertexNum, bool unconvex)
    :QGraphicsItem(parent),_linetype(dbpainter::SOLIDE),
      c(qRgb(0,0,0)),dbp(),lowx(0),lowy(0),highx(800),highy(800),
      vertex(vertexNum),saved_v(vertexNum),fillv(),fillc(qRgb(0,0,0))
{
    dbp.setPenWid(1);
    for (int i=0;i<8;++i)
    {
        tfhand_v.push_back(new transformhandler(this));
        connect(tfhand_v[i],&transformhandler::signalMove,this,&dbvirtualgraph::recvMove);
        connect(tfhand_v[i],&transformhandler::signalMousePress,this,&dbvirtualgraph::moveStatChanged);
        connect(tfhand_v[i],&transformhandler::signalMouseRelease,this,&dbvirtualgraph::moveStatChanged);
    }
    rotateHandler=new transformhandler(this,qRgb(0,0,255));
    rotateHandler->setPos(-100,-100);
    centerHandler=new transformhandler(this,qRgb(0,255,0));
    centerHandler->setPos(400,400);
    connect(rotateHandler,&transformhandler::signalMove,this,&dbvirtualgraph::recvRotate);
    connect(rotateHandler,&transformhandler::signalMousePress,this,&dbvirtualgraph::rotateBeg);
    connect(rotateHandler,&transformhandler::signalMouseRelease,this,&dbvirtualgraph::rotateEnd);
    setFlags(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    stat=0;
    deHovering();
    if (unconvex)
        stat|=status::unConvex;
}
dbvirtualgraph::~dbvirtualgraph()
{
    for (auto &it:tfhand_v)
    {
        delete it;
    }
    delete rotateHandler;
    delete centerHandler;
}

QRectF dbvirtualgraph::boundingRect()const
{
    return QRectF(lowx,lowy,highx-lowx,highy-lowy);
}

void dbvirtualgraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen p;

    p.setColor(fillc);
    painter->setPen(p);
    for (auto &it:fillv)
        painter->drawPoint(it);
    p.setColor(c);
    painter->setPen(p);
    dbp.setPenType(_linetype);
    displayedOutline=dbp.handleOutline(outline);
    //outlineLock.lock();
    for (auto &it:displayedOutline)
        painter->drawPoint(it);
    //outlineLock.unlock();
}
void dbvirtualgraph::setColor(QColor &c)
{
    this->c=c;
}

void dbvirtualgraph::setPenWid(int wid)
{
    dbp.setPenWid(wid);
}

void dbvirtualgraph::setPenType(dbpainter::linetype type)
{
    _linetype=type;
}

void dbvirtualgraph::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void dbvirtualgraph::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            deHovering();
        }
    }

    QGraphicsItem::hoverLeaveEvent(event);
}

void dbvirtualgraph::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            //qDebug()<<"hover on "<<event->scenePos().x()<<" "<<event->scenePos().y();
        }
    }
    QGraphicsItem::hoverMoveEvent(event);
}

void dbvirtualgraph::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            doHovering();
        }
    }
    QGraphicsItem::hoverEnterEvent(event);
}
void dbvirtualgraph::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            QPoint tmp=event->scenePos().toPoint();
            move(tmp.x()-lastPosition.x(),tmp.y()-lastPosition.y());
            lastPosition=tmp;
            //QGraphicsItem::mouseMoveEvent(event);
        }
    }
    else
    {

    }
}
void dbvirtualgraph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            setCursor(QCursor(Qt::ClosedHandCursor));
            lastPosition=event->scenePos().toPoint();
            event->accept();
            emit(selected(this));
        }
    }
    else
    {

    }
    QGraphicsItem::mousePressEvent(event);
}

void dbvirtualgraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            setCursor(QCursor(Qt::CrossCursor));
        }

    }
    else
    {

    }
    QGraphicsItem::mouseReleaseEvent(event);
}
void dbvirtualgraph::move(int dx,int dy)
{
    doMove(dx,dy);
    doPaint();
    positionChanged();
}

void dbvirtualgraph::rotate(double theta,QPoint center)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            doRotate(theta,center);
            doPaint();
            boundingRectAlign();
            int midx=(lowx+highx)/2,midy=(lowy+highy)/2;
            move(centerHandler->scenePos().toPoint().x()-midx,centerHandler->scenePos().toPoint().y()-midy);
            //qDebug()<<centerHandler->scenePos()<<(lowx+highx)/2<<(lowy+highy)/2;
        }
    }
}

void dbvirtualgraph::zoom(QPoint topleft, QPoint lowerright)
{
    if (stat&isFinished)
    {
        if (stat&isActive)
        {
            restore();
            doZoom(topleft,lowerright);
            lowx=topleft.x(),lowy=topleft.y(),highx=lowerright.x(),highy=lowerright.y();
            doPaint();
            boundingRectAlign();
            rotatehandlerAlign();
        }
    }
}
void dbvirtualgraph::doMove(int dx,int dy)
{
    for (auto &it:vertex)
    {
        it.setX(it.x()+dx);
        it.setY(it.y()+dy);
    }
}
void dbvirtualgraph::doRotate(double theta,QPoint center)
{
    if (center!=QPoint(0,0))
        doMove(-center.x(),-center.y());
    double cos_theta=std::cos(theta),sin_theta=std::sin(theta);
    for (auto &it:vertex)
    {
        int x=int(it.x()*cos_theta-it.y()*sin_theta+0.5),y=int(it.x()*sin_theta+it.y()*cos_theta+0.5);
        it.setX(x);
        it.setY(y);
    }
    if (center!=QPoint(0,0))
        doMove(center.x(),center.y());
}


void dbvirtualgraph::doZoom(QPoint topleft, QPoint lowerright)
{
    if (topleft.x()<lowerright.x()&&topleft.y()<lowerright.y())
    {
        int ibeg=topleft.x()+PADSIZE,jbeg=topleft.y()+PADSIZE,
                wid=lowerright.x()-topleft.x()-2*PADSIZE,hei=lowerright.y()-topleft.y()-2*PADSIZE;
        float itime=1.0*(wid)/(highx-lowx-2*PADSIZE),jtime=1.0*(hei)/(highy-lowy-2*PADSIZE);
        for (auto &it:vertex)
        {
            it.setX(ibeg+int((it.x()-lowx-PADSIZE)*itime+0.5));
            it.setY(jbeg+int((it.y()-lowy-PADSIZE)*jtime+0.5));
        }
    }
}
void dbvirtualgraph::positionChanged()
{
	if (outline.size())
	{
        boundingRectAlign();
        transformhandlerAlign();
        rotatehandlerAlign();

	} 
}
void dbvirtualgraph::boundingRectAlign()
{
    if (outline.size())
    {
        highx = lowx = outline[0].x();
        highy = lowy = outline[0].y();
        for (auto &it : outline)
        {
            lowx = MIN(it.x(), lowx);
            lowy = MIN(it.y(), lowy);
            highx = MAX(it.x(), highx);
            highy = MAX(it.y(), highy);
        }
        lowx -= PADSIZE;
        lowy -= PADSIZE;
        highx += PADSIZE;
        highy += PADSIZE;
        prepareGeometryChange();
    }
}
void dbvirtualgraph::transformhandlerAlign()
{
    tfhand_v[7]->setPos(lowx, 1.0*(lowy + highy) / 2);
    tfhand_v[0]->setPos(lowx, lowy);
    tfhand_v[2]->setPos(highx, lowy);
    tfhand_v[3]->setPos(highx, 1.0*(lowy + highy) / 2);
    tfhand_v[1]->setPos(1.0*(lowx + highx) / 2, lowy);
    tfhand_v[5]->setPos(1.0*(lowx + highx) / 2, highy);
    tfhand_v[6]->setPos(lowx, highy);
    tfhand_v[4]->setPos(highx, highy);
    prepareGeometryChange();
}

void dbvirtualgraph::rotatehandlerAlign()
{
    if (!(stat&isRotating))
        centerHandler->setPos(lowx + (highx - lowx)*0.5, lowy + (highy - lowy)*0.5);
    //double R=MIN((highx-lowx)*0.25,(highy-lowy)*0.25);
    double R = 100;
    double r, dx, dy;
    r = std::sqrt(std::pow(std::abs(rotateHandler->x() - centerHandler->x()), 2) +
        std::pow(std::abs(rotateHandler->y() - centerHandler->y()), 2));

    dx = rotateHandler->x() - centerHandler->x();
    dy = rotateHandler->y() - centerHandler->y();
    double cosa = dx / r, sina = dy / r;
    rotateHandler->setPos(centerHandler->x() + cosa * R, centerHandler->y() + sina * R);
    if (stat&isFilled)
        fill();
    prepareGeometryChange();
}

void dbvirtualgraph::doHovering()
{
    for (int i=0;i<8;++i)
        tfhand_v[i]->setVisible(true);
    rotateHandler->setVisible(true);
    //centerHandler->setVisible(true);
}

void dbvirtualgraph::deHovering()
{
    if (!(stat&isSelected))
    {
        for (int i=0;i<8;++i)
            tfhand_v[i]->setVisible(false);
        rotateHandler->setVisible(false);
        centerHandler->setVisible(false);
    }
}
void dbvirtualgraph::resizeTop(int i,int dx,int dy)
{
    tfhand_v[0]->moveBy(0,i==0?0:dy);
    tfhand_v[1]->moveBy(0,i==1?0:dy);
    tfhand_v[2]->moveBy(0,i==2?0:dy);
}

void dbvirtualgraph::resizeButtom(int i,int dx,int dy)
{
    tfhand_v[4]->moveBy(0,i==4?0:dy);
    tfhand_v[5]->moveBy(0,i==5?0:dy);
    tfhand_v[6]->moveBy(0,i==6?0:dy);
}

void dbvirtualgraph::resizeLeft(int i,int dx,int dy)
{
    tfhand_v[0]->moveBy(i==0?0:dx,0);
    tfhand_v[6]->moveBy(i==6?0:dx,0);
    tfhand_v[7]->moveBy(i==7?0:dx,0);
}

void dbvirtualgraph::resizeRight(int i,int dx,int dy)
{
    tfhand_v[2]->moveBy(i==2?0:dx,0);
    tfhand_v[3]->moveBy(i==3?0:dx,0);
    tfhand_v[4]->moveBy(i==4?0:dx,0);
}

void dbvirtualgraph::recvMove(transformhandler *signalOwner,int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1;
    if (signalOwner==tfhand_v[0])
    {
        resizeTop(0,dx,dy);
        resizeLeft(0,dx,dy);
    }
    if (signalOwner==tfhand_v[1])
    {
        resizeTop(1,dx,dy);
    }
    if (signalOwner==tfhand_v[2])
    {
        resizeRight(2,dx,dy);
        resizeTop(2,dx,dy);
    }
    if (signalOwner==tfhand_v[3])
    {
        resizeRight(3,dx,dy);
    }
    if (signalOwner==tfhand_v[4])
    {
        resizeRight(4,dx,dy);
        resizeButtom(4,dx,dy);
    }
    if (signalOwner==tfhand_v[5])
    {
        resizeButtom(5,dx,dy);
    }
    if (signalOwner==tfhand_v[6])
    {
        resizeButtom(6,dx,dy);
        resizeLeft(6,dx,dy);
    }
    if (signalOwner==tfhand_v[7])
    {
        resizeLeft(7,dx,dy);
    }
    zoom(tfhand_v[0]->scenePos().toPoint(),tfhand_v[4]->scenePos().toPoint());
}

void dbvirtualgraph::recvRotate(transformhandler *signalOwner,int x1,int y1,int x2,int y2)
{
    x1=rotateStart.x(),y1=rotateStart.y();
    double r1,r2;
    r1=std::sqrt(std::pow(std::abs(x1-centerHandler->x()),2)+
            std::pow(std::abs(y1-centerHandler->y()),2));
    r2=std::sqrt(std::pow(std::abs(x2-centerHandler->x()),2)+
            std::pow(std::abs(y2-centerHandler->y()),2));
    double sin1,cos1,sin2,cos2,theta1,theta2;
    sin1=1.0*(y1-centerHandler->y())/r1;
    cos1=1.0*(x1-centerHandler->x())/r1;
    sin2=1.0*(y2-centerHandler->y())/r2;
    cos2=1.0*(x2-centerHandler->x())/r2;
    theta1=std::asin(sin1);
    theta1=cos1>0?theta1:(pai-theta1);
    theta2=std::asin(sin2);
    theta2=cos2>0?theta2:(pai-theta2);
    //qDebug()<<theta1*(180/pai)<<theta2*(180/pai);
    double theta=theta2-theta1;
    if (theta<0)
        theta+=2*pai;
    restore();
    rotate(theta,centerHandler->scenePos().toPoint());
}
void dbvirtualgraph::rotateBeg()
{
    stat|=isRotating;
    rotateStart=rotateHandler->scenePos().toPoint();
    save();
}

void dbvirtualgraph::rotateEnd()
{
    stat&=~isRotating;
}
void dbvirtualgraph::save()
{
    saved_v=vertex;
    savedlowx=lowx;
    savedlowy=lowy;
    savedhighx=highx;
    savedhighy=highy;
}

void dbvirtualgraph::restore()
{
    vertex=saved_v;
    lowx=savedlowx;
    lowy=savedlowy;
    highx=savedhighx;
    highy=savedhighy;
}
void dbvirtualgraph::fill()
{
    stat|=isFilled;
    if (stat&unConvex)
    {
        fillv=dbp.polygonfill(vertex,lowx,lowy,highx,highy);
    }
    else
        fillv=dbp.fill(outline,lowx,lowy,highx,highy);
    update();
}
void dbvirtualgraph::defill()
{
    fillv.clear();
    stat&=~isFilled;
    update();
}
void dbvirtualgraph::setFillColor(QColor &c)
{
    fillc=c;
}

int dbvirtualgraph::type() const
{
    return Type;
}
double dbvirtualgraph::getDis(const QPoint &p1,const QPoint &p2)
{
    return std::sqrt(std::pow(std::abs(p1.x()-p2.x()),2)+
                        std::pow(std::abs(p1.y()-p2.y()),2));
}
void dbvirtualgraph::moveStatChanged()
{
    save();
}
