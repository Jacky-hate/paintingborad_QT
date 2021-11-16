#include "colorlabel.h"
#include <QMouseEvent>

colorlabel::colorlabel(QWidget *parent)
    : QLabel(parent)
{

}

colorlabel::~colorlabel()
{

}

void colorlabel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit clicked();
}

void colorlabel::setColor(const QColor &color)
{
    setStyleSheet("QLabel { background-color: " + color.name() + ";}");
}
