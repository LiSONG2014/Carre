#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    float dim_init, dim, pos_x, pos_y, pos_x_max, pos_y_max, zoom;
    void paintEvent(QPaintEvent *event);
    ~MainWindow();

private slots:
    void changeValueX(int x);    
    void changeValueY(int y);
    void changeValueZoom(double Zoom);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
