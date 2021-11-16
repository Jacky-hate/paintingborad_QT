#ifndef DBWORKPLACEVIEW_H
#define DBWORKPLACEVIEW_H
#include <QWidget>
#include <QGraphicsView>
//视图类,是对场景的最终显示
class dbworkplaceview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit dbworkplaceview(QWidget *parent);

protected:

signals:

public slots:
};
#endif // DBWORKPLACEVIEW_H
