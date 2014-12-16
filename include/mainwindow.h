#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QGraphicsScene>
#include "node.h"
#include "algorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:



    // The algorithms
    Algorithm test;


    Ui::MainWindow * ui;
    QGraphicsScene * scene;

public slots:
    void on_setStatusMsg(QString msg);
private slots:
    void on_cycleRemButton_clicked();
};

#endif // MAINWINDOW_H
