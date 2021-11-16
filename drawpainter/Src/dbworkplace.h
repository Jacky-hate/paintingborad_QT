#ifndef DBWORKPLACE_H
#define DBWORKPLACE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include "dbvirtualgraph.h"
//场景类,保存各个形状
class dbworkplace:public QGraphicsScene
{
    Q_OBJECT
public:
    dbworkplace(QObject *parent);
    enum objType{LINE,CIRCLE,ELLIPSE,RECTANGLE,TRIANGLE,POLYGON,BEZIER,BSPLINE,FIT_B,SELECTING,MULTISELECT};
protected:
    objType mode;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void setPen(dbvirtualgraph *item);
    QPoint pbeg,pend;
    dbvirtualgraph *currentItem;
    bool isdrawing;
    bool isLeftButtonPressed;
    int linewidth;
    QColor outlinec,fillc;
    int bezierVertexNum;
    int bezierFitVertexNum;
    int bsplineVertexNum,bsplineVertexk;
    dbpainter::linetype _type;
public slots:
    void selectionMode(objType mode);
    void drawMode(objType mode);
    void clearALL();
    void fillItem();
    void defillItem();
    void recvSelect(dbvirtualgraph *item);
    void setLineWid(const QString &s);
    void setColor(QColor outlinec,QColor fillc);
    void setLineType(const QString &s);
    void deleteItem();
    void setbezierVertexNum(const QString &s);
    void setbezierFitVertexNum(const QString &s);
    void setbsplineVertexNum(const QString &s);
    void setbsplineVertexk(const QString &s);
};

#endif // DBWORKPLACE_H
