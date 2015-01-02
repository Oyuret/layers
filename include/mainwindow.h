#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QFileDialog>
#include "node.h"
#include "algorithm.h"
#include "graph.h"
#include "xml_parser.h"

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

    Graph graph;
    XML_Parser parser;

    // The algorithms
    Algorithm test;


    Ui::MainWindow * ui;
    QGraphicsScene * scene;

public slots:
    void on_setStatusMsg(QString msg);
private slots:
    void on_cycleRemButton_clicked();
    void on_actionLoad_XML_triggered();
};

#endif // MAINWINDOW_H
