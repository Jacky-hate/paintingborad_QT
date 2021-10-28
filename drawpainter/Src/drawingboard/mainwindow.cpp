#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbworkplace.h"
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbworkplace* wp=new dbworkplace(this);
    ui->workplace->setScene(wp);
    ui->workplace->setSceneRect(0,0,ui->workplace->width(),ui->workplace->height());
    connect(ui->clearButton,&QToolButton::clicked,[=](){wp->clearALL();});
    connect(ui->drawlineButton,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::LINE);});
    connect(ui->rectbutton,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::RECTANGLE);});
    connect(ui->drawpolygon,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::POLYGON);});
    connect(ui->drawellipse,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::ELLIPSE);});
    connect(ui->drawbezier,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::BEZIER);});
    connect(ui->drawBspline,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::BSPLINE);});
    connect(ui->drawtriangle,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::TRIANGLE);});
    connect(ui->drawcircle,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::CIRCLE);});
    connect(ui->bezierFit,&QToolButton::clicked,[=](){wp->drawMode(dbworkplace::FIT_B);});

    connect(ui->deletebutton,&QToolButton::clicked,[=](){wp->deleteItem();});
    connect(ui->multiselect,&QToolButton::clicked,[=](){wp->selectionMode(dbworkplace::MULTISELECT);});
    connect(ui->selectButton,&QToolButton::clicked,[=](){wp->selectionMode(dbworkplace::SELECTING);});
    connect(ui->fillButton,&QToolButton::clicked,wp,&dbworkplace::fillItem);
    connect(ui->setting->ui->linewidth,static_cast<void (QSpinBox::*)(const QString&)>(&QSpinBox::valueChanged),wp,&dbworkplace::setLineWid);
    connect(ui->bezierVnum,static_cast<void (QSpinBox::*)(const QString&)>(&QSpinBox::valueChanged),wp,&dbworkplace::setbezierVertexNum);
    connect(ui->bezierFitVnum,static_cast<void (QSpinBox::*)(const QString&)>(&QSpinBox::valueChanged),wp,&dbworkplace::setbezierFitVertexNum);
    connect(ui->bsplinenum,static_cast<void (QSpinBox::*)(const QString&)>(&QSpinBox::valueChanged),wp,&dbworkplace::setbsplineVertexNum);
    connect(ui->bsplinek,static_cast<void (QSpinBox::*)(const QString&)>(&QSpinBox::valueChanged),wp,&dbworkplace::setbsplineVertexk);
    connect(ui->setting->ui->linetype, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),wp,&dbworkplace::setLineType);
    connect(ui->setting,&paintersetting::sendColor,wp,&dbworkplace::setColor);
    //connect(ui->setting->ui->linewidth,static_cast<void (QSpinBox::*)(const QString&)>(&QSpinBox::valueChanged),wp,&dbworkplace::setLineWid);
}

MainWindow::~MainWindow()
{
    delete ui;
}
