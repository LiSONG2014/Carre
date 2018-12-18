#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QColor>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include <QDesktopWidget>

#define MIN(a,b)(((a)<(b))?(a):(b))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size());
    dim_init = 100;
    zoom = 1;
    pos_x=this->width()/2;
    pos_y=this->height()/2;
    ui->spinBox_x->setValue(pos_x);
    ui->spinBox_y->setValue(pos_y);
    ui->SpinBox_zoom->setValue(zoom);
    connect(ui->spinBox_x,SIGNAL(valueChanged(int)),this,SLOT(changeValue()));
    connect(ui->spinBox_y,SIGNAL(valueChanged(int)),this,SLOT(changeValue()));
    connect(ui->SpinBox_zoom,SIGNAL(valueChanged(double)),this,SLOT(changeValue()));

}

void MainWindow::paintEvent(QPaintEvent*event)
{
    QPainter painter(this);
    QPen pen_carre;
    pen_carre.setColor(Qt::black);
    painter.setPen(pen_carre);
    QBrush brush (Qt::black, Qt::SolidPattern);
    painter.setBrush(brush);

    dim = dim_init * zoom;
    QRect rectangle_carre(pos_x-(dim/2), pos_y-(dim/2), dim, dim);
    painter.drawRect(rectangle_carre);
    QMainWindow::paintEvent(event);
}

void MainWindow::changeValue()
{
    pos_x=ui->spinBox_x->value();
    pos_y=ui->spinBox_y->value();
    zoom=ui->SpinBox_zoom->value();
    dim=dim_init*zoom;
    if((pos_x > this->width())||(pos_x<=0))
    { QMessageBox::about(this , "Le carré est dépassé la bordure de l'interface.",
                         "Veuillez modifier la position");
        pos_x=this->width()/2;
        ui->spinBox_x->setValue(pos_x);
    }
    if((pos_y > this->height())||(pos_y<=0))
    { QMessageBox::about(this , "Le carré est dépassé la bordure de l'interface.",
                         "Veuillez modifier la position");
        pos_y=this->height()/2;
        ui->spinBox_y->setValue(pos_y);
    }
    if(((pos_x-dim/2)<0)||((pos_y-dim/2)<0)
            ||((pos_x+dim/2)>this->width())
            ||((pos_y+dim/2)>this->height())
            )
    {
        QMessageBox::about(this , "Le carré est dépassé la bordure de l'interface.",
                           "Veuillez modifier la position, la dimension ou le zoom");

        if((pos_x+dim/2)>this->width())
        {
            if((pos_y+dim/2)>this->height()){
                if((pos_x+dim/2-this->width())>((pos_y+dim/2)-this->height()))
                {
                    dim=(this->width()-pos_x)*2;
                }else{
                    dim=(this->height()-pos_y)*2;
                }
            }else if((pos_y-dim/2)<0)
            {
                if((pos_x+dim/2-this->width())>(dim/2-pos_y))
                {
                    dim=(this->width()-pos_x)*2;
                }else{
                    dim=(this->height()-pos_y)*2;
                }
            }else
            {
                dim=(this->width()-pos_x)*2;
            }

        }else if(pos_x-dim/2<0)
        {
            if((pos_y+dim/2)>this->height()){
                if((dim/2-pos_x)>((pos_y+dim/2)-this->height()))
                {
                    dim=pos_x*2;
                }else
                {
                    dim=(this->height()-pos_y)*2;
                }
            }else if((pos_y-dim/2)<0)
            {
                dim=qMin(pos_x,pos_y);
            }else {dim=pos_x*2;}

        }else
        {
            if((pos_y+dim/2)>this->height())
            {
                dim=(this->height()-pos_y)*2;
            }else if((pos_y-dim/2)<0)
            {
                dim=pos_y*2;
            }
        }

        ui->SpinBox_zoom->setValue(double(dim)/dim_init);
    }
    update();
}


    MainWindow::~MainWindow()
    {
        delete ui;
    }
