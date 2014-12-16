#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    connect(&test,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));

    for(int i=0; i<10; ++i) {
        QString name = QString("B").append(QString::number(i));
        Node* item = new Node(name);
        item->setX(qrand() % ((500 + 1) - (-500)) + (-500));
        item->setY(qrand() % ((500 + 1) - (-500)) + (-500));

        scene->addItem(item);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setStatusMsg(QString msg)
{
    statusBar() -> showMessage(msg);
}

void MainWindow::on_cycleRemButton_clicked()
{
    test.run();
}
