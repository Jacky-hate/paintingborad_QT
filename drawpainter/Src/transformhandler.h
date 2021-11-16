#ifndef TRANSFORMHANDLER_H
#define TRANSFORMHANDLER_H
#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
//变换句柄类,可视作图形按钮
class transformhandler:public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit transformhandler(QGraphicsItem *parentItem = 0,QColor c=qRgb(0,0,0), QObject *parent = 0);
    void setPreviousPosition(const QPointF &pos);
    QPointF previousPosition;

signals:
    void signalMousePress();
    void signalMouseRelease();
    void signalMove(transformhandler *signalOwner, int x1, int y1, int x2, int y2);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QBrush _b;
public slots:

private:

};

#endif // TRANSFORMHANDLER_H
