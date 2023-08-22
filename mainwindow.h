#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include <QDebug>
#include <QPainter>
#include <QColor>
#include "qpaintbox.h"

#include <QTime>
#include <QDateTime> //devuelve dia, util para el cartel
#include <QTimer>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseCloseEvent(QMouseEvent *event);

    void onTimer();

private:
    QTimer *timer;
    QTime *myTime;
    QDateTime *myDateTime;

    int lastPosX, lastPosY;
    bool mouseIsPressed;
    bool F_click;
    int minCount=0;

    QPoint offset;

    Ui::MainWindow *ui;
    QPaintBox *QPaintBox1;
};
#endif // MAINWINDOW_H
