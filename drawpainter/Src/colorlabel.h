#ifndef colorlabel_H
#define colorlabel_H
#include <QLabel>
//颜色标签类，用于在gui上显示所选的颜色
class QMouseEvent;

class colorlabel : public QLabel
{
    Q_OBJECT
public:
    explicit colorlabel(QWidget *parent = 0);
    ~colorlabel();

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

public slots:
    void setColor(const QColor &color);
};


#endif // colorlabel_H
