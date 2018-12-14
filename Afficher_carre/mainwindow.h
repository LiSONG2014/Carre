#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QPainter>
#include <QPixmap>
#include <QTransform>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);

public slots:
    void Affi();
private:
    Ui::MainWindow *ui;
    int pos_x, pos_y, dim, zoom;
};

#endif // MAINWINDOW_H
