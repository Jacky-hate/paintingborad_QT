#ifndef PAINTERSETTING_H
#define PAINTERSETTING_H

#include <QWidget>
#include "ui_paintersetting.h"
//画笔设置gui类
namespace Ui {
class psetting;
}

class paintersetting : public QWidget
{
    Q_OBJECT

public:
    explicit paintersetting(QWidget *parent = 0);
    ~paintersetting();
    void paintersetting::setFillc(const QColor &color);
    void paintersetting::setOutlinec(const QColor &color);
    Ui::psetting *ui;
signals:
    void sendColor(QColor outlinec,QColor fillc);
protected:
    QColor outlinec;
    QColor fillc;
};

#endif // PAINTERSETTING_H
