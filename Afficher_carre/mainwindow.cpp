#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size());
    ui->spinBox_X->setValue(this->width()/2);
    ui->spinBox_Y->setValue(this->height()/2);
    pos_x=ui->spinBox_X->value();
    pos_y=ui->spinBox_Y->value();
    dim=ui->spinBox_Dimention->value();
    zoom=ui->doubleSpinBox_Zoom->value();
    dim=dim*zoom;
    connect(ui->spinBox_Dimention,SIGNAL(valueChanged(int)),this, SLOT(Affi()));
    connect(ui->spinBox_X,SIGNAL(valueChanged(int)),this, SLOT(Affi()));
    connect(ui->spinBox_Y,SIGNAL(valueChanged(int)),this, SLOT(Affi()));
    connect(ui->doubleSpinBox_Zoom,SIGNAL(valueChanged(int)),this, SLOT(Affi()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Affi()
{
    pos_x=ui->spinBox_X->value();
    pos_y=ui->spinBox_Y->value();
    dim=ui->spinBox_Dimention->value();
    zoom=ui->doubleSpinBox_Zoom->value();
    dim=dim*zoom;
    if(((pos_x-dim/2)<0)||((pos_y-dim/2)<0)
            ||((pos_x+dim/2)>this->width())
            ||((pos_y+dim/2)>this->height())
            )
    {
        QMessageBox::about(this , "Le carré est dépassé la bordure de l'interface.",
                                  "Veuillez modifier la position, la dimension ou le zoom");
    }else{
        update();
    }
}



void MainWindow::paintEvent(QPaintEvent *e)
{
   QPainter p(this);
   QPen pen ;
   pen.setColor(QColor(255,0,0));
   QBrush brush(QColor(255,0,0));
   p.setPen(pen);
   p.setBrush(brush);
   p.drawRect((pos_x-dim/2),(pos_y-dim/2),dim,dim); //carre au milieu
  // QMainWindow::paintEvent(e) ;
}
