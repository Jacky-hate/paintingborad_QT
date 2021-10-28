#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <QPoint>

using namespace std;
struct Spot
{
    int x, y;
    Spot(int dx, int dy)
    {
        x = dx;
        y = dy;
    };
    Spot() {};

};


struct Edge
{
    int ymax;  //边的上端点的y坐标
    float x, deltax;  //边的下端点的x坐标    deltax：边的斜率的倒数
    Edge* nextEdge = NULL;
    Edge(Spot a, Spot b)
    {
        ymax = (a.y > b.y ? a.y : b.y);
        x = (a.y > b.y ? b.x : a.x);
        deltax = (a.y == b.y ? 99999 : (a.x - b.x) * 1.0 / (a.y - b.y));
        nextEdge = NULL;
    };
    Edge() { nextEdge = NULL; };
    void inert(Spot a, Spot b)
    {
        Edge* n = new Edge(a, b);
        Edge* e = nextEdge;
        Edge* nmid = NULL;
        if (nextEdge == NULL)
        {
            nextEdge = n;
            n->nextEdge = NULL;
            return;
        }
        if (e->x > n->x)
        {
            nextEdge = n;
            n->nextEdge = e;
            return;
        }
        else if (e->x == n->x && e->deltax > n->deltax)
        {
            nextEdge = n;
            n->nextEdge = e;
            return;
        }
        while (e->nextEdge != NULL && e->nextEdge->x < n->x)
        {
            e = e->nextEdge;
        }
        if (e->nextEdge == NULL)
        {
            e->nextEdge = n;
            n->nextEdge = NULL;
        }
        else if (e->nextEdge->x > n->x)
        {
            nmid = e->nextEdge;
            e->nextEdge = n;
            n->nextEdge = nmid;
        }
        else
        {
            while (e->nextEdge != NULL &&e->nextEdge->x == n->x && e->nextEdge->deltax < n->deltax)
            {
                e = e->nextEdge;
            }
            nmid = e->nextEdge;
            e->nextEdge = n;
            n->nextEdge = nmid;
        }
    };
    void inert(float a_x, int a_ymax, float a_deltax)
    {
        Edge* n = new Edge;
        Edge* nmid = NULL;
        n->x = a_x;
        n->ymax = a_ymax;
        n->deltax = a_deltax;
        n->nextEdge = NULL;
        Edge* e = nextEdge;
        if (nextEdge == NULL)
        {
            nextEdge = n;
            n->nextEdge = NULL;
            return;
        }
        if (e->x > n->x)
        {
            nextEdge = n;
            n->nextEdge = e;
            return;
        }
        else if (e->x == n->x && e->deltax > n->deltax)
        {
            nextEdge = n;
            n->nextEdge = e;
            return;
        }
        while (e->nextEdge != NULL && e->nextEdge->x < a_x)
        {
            e = e->nextEdge;
        }
        if (e->nextEdge == NULL)
        {
            e->nextEdge = n;
            n->nextEdge = NULL;
        }
        else if (e->nextEdge->x > a_x)
        {
            nmid = e->nextEdge;
            e->nextEdge = n;
            n->nextEdge = nmid;
        }
        else
        {
            while (e->nextEdge != NULL && e->nextEdge->x == a_x && e->nextEdge->deltax < a_deltax)
            {
                e = e->nextEdge;
            }
            nmid = e->nextEdge;
            e->nextEdge = n;
            n->nextEdge = nmid;
        }
    };
};

void ScanLine(Spot p[], int SIZE, vector<QPoint> &res)  //数组p的个数不限制  需要SIZE作为顶点个数
{
    Edge et[2000];
    //建立et表
    for (int i = 0; i < SIZE; i++)
    {
        if (p[i].y < p[(i + 1) % SIZE].y)
        {
            et[p[i].y].inert(p[i], p[(i + 1) % SIZE]);
        }
        else if (p[i].y > p[(i + 1) % SIZE].y)
        {
            et[p[(i + 1) % SIZE].y].inert(p[i], p[(i + 1) % SIZE]);
        }
    }
    Edge* ael = new Edge;
    Edge* n = NULL, *nmid = NULL;
    int y;
    for (y = 0; y < 1000; y++)
    {
        n = ael;
        while (n->nextEdge != NULL)  //去掉最高点小于y的边
        {
            if (n->nextEdge->ymax < y)
            {
                nmid = n->nextEdge;
                n->nextEdge = n->nextEdge->nextEdge;
                delete nmid;
            }
            else
                n = n->nextEdge;
        }
        //更新x的值
        n = ael->nextEdge;
        while (n != NULL)
        {
            n->x = n->x + n->deltax;
            n = n->nextEdge;
        }
        //画点
        n = ael->nextEdge;
        while (n != NULL)
        {
            for (int i = n->x; i <= n->nextEdge->x; i++)
            {
                res.push_back(QPoint(i,y));//填充像素点(i,y)
            }
            n = n->nextEdge->nextEdge;
        }
        //添加新的边
        if (et[y].nextEdge != NULL)
        {
            n = et[y].nextEdge;
            while (n != NULL)
            {
                ael->inert(n->x, n->ymax, n->deltax);
                res.push_back(QPoint(n->x, y));
                n = n->nextEdge;
            }
        }
    }
};
