#include "dbpainter.h"
#include <QDebug>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <map>
dbpainter::dbpainter()
    :type(SOLIDE),width(1)
{
}

std::vector<QPoint> dbpainter::drawPoint(const QPoint &p)
{
    int x=p.x(),y=p.y();
    std::vector<QPoint> res;
    for (int i=x-(width-1);i<=x+(width-1);++i)
        for (int j=y-(width-1);j<=y+(width-1);++j)
        {
            res.push_back(QPoint(i,j));
        }
    return res;
}
template <typename T>
int Bresenham(T x1, T y1, T x2, T y2, QPoint* &vertices)
{
    if (y2 == y1)
    {
        if (x1 > x2)
            std::swap(x1, x2);
        int size = x2 - x1 + 1;
        vertices = new QPoint[size];
        for (int i = 0; i < size; ++i, ++x1)
            vertices[i] = QPoint(x1, y1);
        return size;
    }
    if (x2 == x1)
    {
        if (y1 > y2)
            std::swap(y1, y2);
        int size = y2 - y1 + 1;
        vertices = new QPoint[size];
        for (int i = 0; i < size; ++i, ++y1)
            vertices[i] = QPoint(x1, y1);
        return size;
    }
    T de1, de2, e;
    double k = ((double)y2 - y1) / (x2 - x1);
    int size, dx, dy;
    if (abs(k) > 1)
    {
        if (y2 < y1)
            std::swap(y1, y2), std::swap(x1, x2);
        size = y2 - y1 + 1;
        dx = 0;
        dy = 1;
        de1 = abs(y2 - y1);
        de2 = abs(x2 - x1);
    }
    else
    {
        if (x2 < x1)
            std::swap(y1, y2), std::swap(x1, x2);
        size = x2 - x1 + 1;
        dx = 1;
        dy = 0;
        de1 = abs(x2 - x1);
        de2 = abs(y2 - y1);
    }
    e = -de1;
    vertices = new QPoint[size + 1];
    for (int i = 0; i < size; ++i)
    {
        vertices[i] = QPoint(x1, y1);
        int f = e >= 0;
        x1 += (f | dx)*(dx ? 1 : (k / abs(k)));
        y1 += (f | dy)*(dy ? 1 : (k / abs(k)));
        e += 2 * de2;
        if (f)
            e -= 2 * de1;    
    }
    vertices[size] = QPoint(x2, y2);
    return size + 1;
}
std::vector<QPoint> dbpainter::drawLine(const QPoint &p1, const QPoint &p2)
{
    QPoint *v=NULL;
    int size=Bresenham<int>(p1.x(),p1.y(),p2.x(),p2.y(),v);
    std::vector<QPoint> res;
    for (int i=0;i<size;++i)
        insertV(res,v[i]);
    delete[] v;
    return res;
}
inline int Round(const float a) { return static_cast<int>(a + 0.5); }
std::vector<QPoint> dbpainter::drawEllipse(const QPoint &center, int Rx, int Ry)
{
    std::vector<QPoint> res;
    int xCenter=center.x(),yCenter=center.y();
    int Rx2 = Rx * Rx;
    int Ry2 = Ry * Ry;
    int doubleRx2 = 2 * Rx2;
    int doubleRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = doubleRx2 * y;
    // Plot the initial point in each quadrant
    insertV(res,QPoint(xCenter + x, yCenter + y));
    insertV(res,QPoint(xCenter - x, yCenter + y));
    insertV(res,QPoint(xCenter + x, yCenter - y));
    insertV(res,QPoint(xCenter - x, yCenter - y));
    /* Region 1 */
    p = Round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
    while (px < py) {
        x++;
        px += doubleRy2;
        if (p < 0) {
            p += Ry2 + px;
        }
        else {
            y--;
            py -= doubleRx2;
            p += Ry2 + px - py;
        }
        insertV(res,QPoint(xCenter + x, yCenter + y));
        insertV(res,QPoint(xCenter - x, yCenter + y));
        insertV(res,QPoint(xCenter + x, yCenter - y));
        insertV(res,QPoint(xCenter - x, yCenter - y));
    }
    /* Region 2 */
    p = Round(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
    while (y > 0) {
        y--;
        py -= doubleRx2;
        if (p > 0) {
            p += Rx2 - py;
        }
        else {
            x++;
            px += doubleRx2;
            p += Rx2 - py + px;
        }
        insertV(res,QPoint(xCenter + x, yCenter + y));
        insertV(res,QPoint(xCenter - x, yCenter + y));
        insertV(res,QPoint(xCenter + x, yCenter - y));
        insertV(res,QPoint(xCenter - x, yCenter - y));
    }
    return res;
}

void dbpainter::setPenWid(int wid)
{
    width=wid;
}

void dbpainter::setPenType(dbpainter::linetype type)
{
    this->type=type;
}

std::vector<QPoint> dbpainter::fill(std::vector<QPoint> &outline,int lowx,int lowy,int highx,int highy)
{
    std::vector<QPoint> res;
    int wid=highx-lowx+1,hei=highy-lowy+1;
    std::vector<std::vector<int>> mat(wid,std::vector<int>(hei,0));
    for (auto &it:outline)
    {
        mat[it.x()-lowx][it.y()-lowy]=1;
    }
    for (int i=0;i<wid;++i)
    {
        for (int j=0;j<hei;++j)
            if (mat[i][j]!=1)
                mat[i][j]=2;
            else
                break;
        for (int j=hei-1;j>=0;--j)
            if (mat[i][j]!=1)
                mat[i][j]=2;
            else
                break;
    }
    for (int j=0;j<hei;++j)
    {
        for (int i=0;i<wid;++i)
            if (mat[i][j]!=1)
                mat[i][j]=2;
            else
                break;
        for (int i=wid-1;i>=0;--i)
            if (mat[i][j]!=1)
                mat[i][j]=2;
            else
                break;
    }
    for (int j=0;j<hei;++j)
        for (int i=0;i<wid;++i)
            if (mat[i][j]==0)
                res.push_back(QPoint(i+lowx, j+lowy));
    return res;
}
struct Edge
{
    int ymax;
    float x,deltax;
    friend bool operator <(const Edge &e1,const Edge &e2)
    {
        return e1.x==e2.x?e1.deltax<=e2.deltax:e1.x<e2.x;
    }
    Edge(int ymax,float x,float deltax)
        :ymax(ymax),x(x),deltax(deltax)
    {
    }
};

void ScanLine(std::vector<QPoint> &pointv, std::vector<QPoint> &res)
{
    int size=pointv.size();
    //建立ET表
    std::map<int,std::list<Edge>> ET;
    int _min=0x3f3f3f3f,_max=0;
    for (int i=0;i<size;++i)
    {
        int j=(i+1)%size;
        auto from=pointv[i],to=pointv[j];
        if (from.y()==to.y())//跳过与x轴平行的边
            continue;
        if (from.y()>to.y())
            std::swap(from,to);
        int ymax=to.y(),ymin=from.y();
        _min=MIN(_min,ymin);
        _max=MAX(_max,ymax);
        float x=from.x();
        float deltax=1.0*(to.x()-from.x())/(to.y()-from.y());
        Edge e(ymax,x,deltax);
        auto it=ET.find(ymin);
        if (it!=ET.end())
        {
            it->second.push_back(e);
        }
        else
        {
            std::list<Edge> _list;
            _list.push_back(e);
            ET[ymin]=_list;
        }
    }
    for (auto &it:ET)
        it.second.sort();

    //在[y_min,y_max]内遍历y值
    std::list<Edge> AEL;
    for (int y=_min;y<=_max;++y)
    {
        for(auto it=AEL.begin();it!=AEL.end();){
            if(it->ymax==y)//若边已结束则删除
            {
                AEL.erase(it++);
            }
            else//否则更新x
            {
                it->x+=it->deltax;
                it++;
            }
        }
        auto it=ET.find(y);//加入符合条件的边
        if (it!=ET.end())
        {
            for (auto &_it:it->second)
                AEL.push_back(_it);
            AEL.sort();
        }
        for(auto it=AEL.begin();it!=AEL.end();){
            int xlow=int(it->x+0.5),xhigh=int((++it)->x+0.5);
            for (int x=xlow;x<=xhigh;++x)//填充
                res.push_back(QPoint(x,y));
            ++it;
        }
    }
}

std::vector<QPoint> dbpainter::polygonfill(std::vector<QPoint> &pointv,int lowx,int lowy,int highx,int highy)
{
    std::vector<QPoint> res;
    ScanLine(pointv,res);
    return res;
}
void dbpainter::insertV(std::vector<QPoint> &pointv,QPoint p)
{
    auto tmp=drawPoint(p);
    pointv.insert(pointv.end(),tmp.begin(),tmp.end());
}
std::vector<QPoint> dbpainter::drawBezier(std::vector<QPoint> &vertex,const int outlineNum)
{
    std::vector<QPoint> res;
    int size=vertex.size();
    std::vector<std::vector<std::vector<double>>> para(size,std::vector<std::vector<double>>(size,std::vector<double>(2)));
    for (int i=0;i<size;++i)
        para[i][i][0]=vertex[i].x(),para[i][i][1]=vertex[i].y();
    for (double t=0;t<1;t+=(1.0/outlineNum))
    {
        for (int i=1;i<size;++i)
        {
            for (int j=0;j<size-i;++j)
            {
                para[j][j+i][0]=(1-t)*para[j][j+i-1][0]+t*para[j+1][j+i][0];
                para[j][j+i][1]=(1-t)*para[j][j+i-1][1]+t*para[j+1][j+i][1];
            }
        }
        res.push_back(QPoint(para[0][size-1][0],para[0][size-1][1]));
    }
    return res;
}
std::vector<QPoint> dbpainter::drawBspline(std::vector<QPoint> &vertex,std::vector<int> &controlv)
{
    std::vector<QPoint> res;
    const int outlineNum=1000;
    int size=vertex.size(),csize=controlv.size()-size-1;
    double u_ui,uik_ui,uik1_u,uik1_ui1,x,y;
    std::vector<std::vector<double>> para(csize+size,std::vector<double>(csize+1));
    for (double t=0;t<1;t+=(1.0/outlineNum))
    {
        for (int i=0;i<csize+size;++i)
        {
            para[i][0]=(t>=1.0*controlv[i]/outlineNum&&t<=1.0*controlv[i+1]/outlineNum)?1:0;
        }
        for (int j=1;j<=csize;++j)
        {
            for (int i=0;i<csize+size-j;++i)
            {
                u_ui=t-1.0*controlv[i]/outlineNum;
                uik_ui=1.0*controlv[i+j]/outlineNum-1.0*controlv[i]/outlineNum;
                if (uik_ui==0)
                    uik_ui=1;
                uik1_u=1.0*controlv[i+j+1]/outlineNum-t;
                uik1_ui1=1.0*controlv[i+j+1]/outlineNum-1.0*controlv[i+1]/outlineNum;
                if (uik1_ui1==0)
                    uik1_ui1=1;
                para[i][j]=(u_ui/uik_ui)*para[i][j-1]+(uik1_u/uik1_ui1)*para[i+1][j-1];
            }
        }
        x=y=0;
        for (int i=0;i<size;++i)
        {
            x+=vertex[i].x()*para[i][csize];
            y+=vertex[i].y()*para[i][csize];
        }
        res.push_back(QPoint(x,y));
    }
    return res;
}
std::vector<QPoint> dbpainter::handleOutline(std::vector<QPoint> &outline)
{
    std::vector<QPoint> res;
    switch (type)
    {
    case SOLIDE:
    {
        res=outline;
        break;
    }
    case DOTTED:
    {
        for (int i=0;i<outline.size();++i)
            if (i&(0x8<<width*2))
                res.push_back(outline[i]);
        break;
    }
    case DASHED:
    {
        for (int i=0;i<outline.size();++i)
            if (i&(4<<width*2))
                res.push_back(outline[i]);
        break;
    }
    }
    return res;
}
inline double getDis(const QPoint &p1,const QPoint &p2)
{
    return std::sqrt(std::pow(std::abs(p1.x()-p2.x()),2)+
                        std::pow(std::abs(p1.y()-p2.y()),2));
}
void dbpainter::getControlPoint(const QPoint &pt, const QPoint &p1, const QPoint &p2,
                                   QPoint &control1, QPoint &control2, double ratio)
{
    double length1 = getDis(p1,pt);
    double length2 = getDis(p2,pt);

    double v = length2/(length1+ 0.000001);

    QPoint delta;
    if(v>1)
    {
        delta = p1 - (pt + ( p2 - pt) / (v + 0.000001));
    }
    else
    {
        delta = pt + (p1-pt) * v - p2 ;
    }

    delta *= ratio;
    control1 = pt + delta;
    control2 = pt - delta;
}
std::vector<QPoint> dbpainter::drawBezierFit(std::vector<QPoint> &vertex)
{
    std::vector<QPoint> res,t;
    if (vertex.size()==2)
    {
        res=drawBezier(vertex,250);
        return res;
    }
    QPoint c12,c21,c22;
    c12=vertex[0];
    for (int i=1;i<vertex.size()-1;++i)
    {
        getControlPoint(vertex[i],vertex[i-1],vertex[i+1],c21,c22,0.6);
        t=std::vector<QPoint>{ vertex[i-1],c12,c21,vertex[i]};
        t=drawBezier(t,250);
        res.insert(res.end(),t.begin(),t.end());
        c12=c22;
    }
    c21=vertex[vertex.size()-1];
    t=std::vector<QPoint>{vertex[vertex.size()-2],c12,c21,vertex[vertex.size()-1]};
    t=drawBezier(t,250);
    res.insert(res.end(),t.begin(),t.end());
    return res;
}

/*
bfs种子填充,速度过慢
int wid=highx-lowx+1,hei=highy-lowy+1;
std::set<std::pair<int,int>> _set;
for (auto &it:pointv)
    _set.insert(std::make_pair(it.x(),it.y()));
std::vector<std::vector<bool>> vis(wid,std::vector<bool>(hei,0));
QPoint seed= QPoint((lowx+highx)/2, (lowy+highy)/2);

std::queue<QPoint> q;
q.push(seed);
vis[seed.x()-lowx][seed.y()-lowy]=1;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
while(!q.empty())
{
    auto cur=q.front();q.pop();
    res.push_back(cur);
    for (int i=0;i<4;++i)
    {
        int x=cur.x()+dx[i],y=cur.y()+dy[i];
        if (x>=lowx&x<=highx&&y>=lowy&&y<=highy&&_set.count(std::make_pair(x,y))==0&&!vis[x-lowx][y-lowy])
        {
            q.push(QPoint(x,y));
            vis[x - lowx][y - lowy] =1;
        }
    }
}*/
