#include "paintersetting.h"
#include <QColorDialog>
#include <QDebug>
#include <QRgb>

paintersetting::paintersetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::psetting)
{
    ui->setupUi(this);
    ui->fillc->setColor(qRgb(255,255,0));
    ui->outlinec->setColor(qRgb(0,0,0));
    connect(ui->fillc, &colorlabel::clicked,
            [=](){
        QColorDialog dialog;
        connect(&dialog, &QColorDialog::colorSelected, this, &paintersetting::setFillc);
        dialog.exec();
    });
    connect(ui->outlinec, &colorlabel::clicked,
            [=](){
        QColorDialog dialog;
        connect(&dialog, &QColorDialog::colorSelected, this, &paintersetting::setOutlinec);
        dialog.exec();
    });
}
void paintersetting::setFillc(const QColor &color)
{
    ui->fillc->setColor(color);
    fillc=color;
    emit sendColor(outlinec,fillc);

}

void paintersetting::setOutlinec(const QColor &color)
{
    ui->outlinec->setColor(color);
    outlinec=color;
    emit sendColor(outlinec,fillc);

}
paintersetting::~paintersetting()
{
    delete ui;
}

