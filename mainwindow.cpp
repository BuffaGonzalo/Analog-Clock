#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //creamos la variable que declaramos
    QPaintBox1 = new QPaintBox(0,0,ui->widget); //el padre es el widget

    timer = new QTimer(this);
    timer->start(10);

    connect(timer, &QTimer::timeout,this,&MainWindow::onTimer); //obtenemos la hora de la PC, this seria en la pestaña actual

    connect(QPaintBox1,&QPaintBox::OnMousePress,this,&MainWindow::mousePressEvent);
    connect(QPaintBox1,&QPaintBox::OnMouseRelease,this,&MainWindow::mouseReleaseEvent);
    connect(QPaintBox1,&QPaintBox::OnMouseMove,this,&MainWindow::mouseMoveEvent);
    connect(QPaintBox1,&QPaintBox::OnMouseDoubleClick,this,&MainWindow::mouseCloseEvent);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        lastPosX = event->pos().x();
        lastPosY = event->pos().y();
        qDebug() << QString().number(lastPosX) + "," + QString().number(lastPosY);
        mouseIsPressed = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mouseIsPressed = false;
        qDebug() << "MOUSE RELEASED";
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(mouseIsPressed){
        int newPosX = event->pos().x();
        int newPosY = event->pos().y();
        int dx = newPosX - lastPosX;
        int dy = newPosY - lastPosY;

        if(dx<10 && dx>-10)
            dx = 0;
        if(dy<10 && dy>-10)
            dy = 0;

        this->setGeometry(this->geometry().left()+dx, this->geometry().top()+dy, this->width(), this->height());
    }
}

void MainWindow::mouseCloseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        close();
    }
}

void MainWindow::onTimer(){
    //variable local
    QPainter paint(QPaintBox1->getCanvas());

    QTime myTime;
    myTime = QTime::currentTime();

    QPen pen;
    QBrush brush; //
    QPoint secArrow[8];
    QPoint minArrow[6];
    QPoint hourArrow[6];

    int minCount=0;

    pen.setWidth(3);
    pen.setColor(Qt::red);
    paint.setPen(pen);
    paint.drawLine(0, ui->widget->height()/2, ui->widget->width(), ui->widget->height()/2);

    pen.setColor(Qt::darkGreen);
    paint.setPen(pen);

    brush.setColor(Qt::darkGreen);
    brush.setStyle(Qt::SolidPattern);
    paint.setBrush(brush);
    paint.drawEllipse(0,0,600,600); //dos primeras son el punto central de la circunf

    pen.setColor(Qt::white);
    paint.setPen(pen);
    brush.setColor(Qt::white);
    paint.setBrush(brush);

    paint.save();
    paint.translate(25,25);
    paint.drawEllipse(0,0,550,550);
    paint.restore();
    paint.save();

    paint.save();
    paint.translate(300,300);
    for(int i=1;i<=60;i++){
        paint.rotate(6);
        if(i%5==0){
            pen.setColor(Qt::darkGreen);
            paint.setPen(pen);
            paint.drawLine(0,275,0,240);
        } else{
            pen.setColor(Qt::green);
            paint.setPen(pen);
            paint.drawLine(0,275,0,260);
        }
    }
    paint.restore();
    paint.save();

    //imprimimos el dia,mes y año
    QFont font("Arial", 14);
    font.setBold(true);
    pen.setColor(Qt::black);
    paint.setPen(pen);
    paint.setFont(font);
    paint.drawText(260,500,QDateTime::currentDateTime().toString("dd/MM/yyyy")); // HH:mm:ss

    //dibujamos las agujas
    //aguja de hora
    hourArrow[0].setX(0);
    hourArrow[0].setY(0);
    hourArrow[1].setX(5);
    hourArrow[1].setY(0);
    hourArrow[2].setX(10);
    hourArrow[2].setY(150);
    hourArrow[3].setX(0);
    hourArrow[3].setY(180);
    hourArrow[4].setX(-10);
    hourArrow[4].setY(150);
    hourArrow[5].setX(-5);
    hourArrow[5].setY(0);

    pen.setColor(Qt::blue);
    paint.setPen(pen);
    brush.setColor(Qt::blue);
    paint.setBrush(brush);

    paint.save();
    paint.translate(300,300);
    if(minCount==20){
        paint.rotate((30*myTime.hour()+180)+((myTime.msec()/30)));
        minCount=0;
    } else{
        paint.rotate(30*myTime.hour()+180);
    }
    paint.drawPolygon(hourArrow,6);
    paint.restore();
    paint.save();

    //aguja de minutos
    minArrow[0].setX(0);
    minArrow[0].setY(0);
    minArrow[1].setX(5);
    minArrow[1].setY(0);
    minArrow[2].setX(10);
    minArrow[2].setY(210);
    minArrow[3].setX(0);
    minArrow[3].setY(240);
    minArrow[4].setX(-10);
    minArrow[4].setY(210);
    minArrow[5].setX(-5);
    minArrow[5].setY(0);

    pen.setColor(Qt::yellow);
    paint.setPen(pen);
    brush.setColor(Qt::yellow);
    paint.setBrush(brush);

    paint.save();
    paint.translate(300,300);

    if(myTime.second()==59){
        paint.rotate(180+(myTime.minute()*6)+((myTime.msec()/150)));
        minCount++;
    } else{
        paint.rotate(180+(myTime.minute()*6));
    }

    paint.drawPolygon(minArrow,6);
    paint.restore();
    paint.save();

    //aguja de segundos
    secArrow[0].setX(0);
    secArrow[0].setY(0);
    secArrow[1].setX(5);
    secArrow[1].setY(0);
    secArrow[2].setX(5);
    secArrow[2].setY(220);
    secArrow[3].setX(10);
    secArrow[3].setY(220);
    secArrow[4].setX(0);
    secArrow[4].setY(240);
    secArrow[5].setX(-10);
    secArrow[5].setY(220);
    secArrow[6].setX(-5);
    secArrow[6].setY(220);
    secArrow[7].setX(-5);
    secArrow[7].setY(0);

    pen.setColor(Qt::red);
    paint.setPen(pen);
    brush.setColor(Qt::red);
    paint.setBrush(brush);

    paint.save();
    paint.translate(300,300);
    paint.rotate(6*myTime.second()+myTime.msec()/100*0.6+180);
    paint.drawPolygon(secArrow,8); //vector, cantidad de elemetos
    paint.restore();
    paint.save();

    //centro de reloj
    pen.setColor(Qt::darkGray);
    paint.setPen(pen);
    brush.setColor(Qt::darkGray);
    paint.setBrush(brush);

    paint.resetTransform();
    paint.translate(284,284);
    paint.drawEllipse(0,0,32,32);

    QPaintBox1->update();
}
