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
    ui->spinBox_x->setValue(this->width()/2);
    ui->spinBox_y->setValue(this->height()/2);
    ui->SpinBox_zoom->setValue(zoom);
    connect(ui->spinBox_x,SIGNAL(valueChanged(int)),this,SLOT(changeValueX(int)));
    connect(ui->spinBox_y,SIGNAL(valueChanged(int)),this,SLOT(changeValueY(int)));
    connect(ui->SpinBox_zoom,SIGNAL(valueChanged(double)),this,SLOT(changeValueZoom(double)));

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

void MainWindow::changeValueX(int X)
{
    if ((X-(dim/2)) < 0)
    {
        pos_x = (dim/2);
        ui->spinBox_x->setValue(pos_x);
        repaint();
    }
    if ((X+(dim/2)) > this->width())
    {
        pos_x = this->width() - (dim/2);
        ui->spinBox_x->setValue(pos_x);
        repaint();
    }
    if ( ((X-(dim/2))>=0) && ((X+(dim/2)) <= this->width()) )
    {
        pos_x = X;
        repaint();
    }
}

void MainWindow::changeValueY(int Y)
{
    if ((Y-(dim/2)) < 0)
    {
        pos_y = (dim/2);
        ui->spinBox_y->setValue(pos_y);
        repaint();
    }
    if ((Y+(dim/2)) > this->height())
    {
        pos_y = this->height() - (dim/2);
        ui->spinBox_y->setValue(pos_y);
        repaint();
    }
    if ( ((Y-(dim/2)) >= 0) && ((Y+(dim/2)) <= this->height()) )
    {
        pos_y = Y;
        repaint();
    }
}

void MainWindow::changeValueZoom(double Zoom)
{
    if( ((dim_init*Zoom)<=this->width()) && ((dim_init*Zoom)<=this->height())
            && ((dim_init*Zoom)+pos_y<=this->height()) && ((dim_init*Zoom)+pos_x<=this->width()) && (pos_x-dim>=0) && (pos_y-dim/2>=0))
    {
        zoom = Zoom;
        repaint();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
