#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    /*QBrush red(Qt::red);
    QBrush black(Qt::black);

    QPen blackPen(Qt::black);

    QGraphicsRectItem* rect = scene->addRect(0,0,50,50,blackPen,red);
    scene->addRect(-100,0,50,50,blackPen,red);
    scene->addRect(0,-100,50,50,blackPen,red);
    scene->addRect(100,100,50,50,blackPen,red);
    scene->addRect(1000,0,50,50,blackPen,red);
    scene->addRect(0,1000,50,50,blackPen,red);
    scene->addRect(1000,1000,50,50,blackPen,red);*/

    for(int i=0; i<10; ++i) {
        QString name = QString("B").append(QString::number(i));
        BlockItem* item = new BlockItem(name, 60, 60);
        item->setX(qrand() % ((500 + 1) - (-500)) + (-500));
        item->setY(qrand() % ((500 + 1) - (-500)) + (-500));

        scene->addItem(item);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
