#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QFileDialog>
#include "node.h"
#include "edgeitem.h"
#include "cyclereduction.h"
#include "assignlayers.h"
#include "insertdummynodes.h"
#include "reducecrossings.h"
#include "balancegraph.h"
#include "rendergraph.h"
#include "graph.h"
#include "xml_parser.h"
#include "createibedobed.h"
#include "altreducecrossings.h"

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

    // The normal algorithms
    CycleReduction removeCycles;
    AssignLayers assignLayers;
    InsertDummyNodes insertDummyNodes;
    ReduceCrossings reduceCrossings;
    BalanceGraph balanceGraph;
    RenderGraph renderGraph;

    // My algorithms
    CreateIbedObed createIbedObed;
    AltReduceCrossings altReduceCrossings;


    Ui::MainWindow * ui;
    QGraphicsScene * scene;

public slots:
    void on_setStatusMsg(QString msg);
private slots:
    void on_cycleRemButton_clicked();
    void on_actionLoad_XML_triggered();
    void on_layeringButton_clicked();
    void on_normalDummyNodesButton_clicked();
    void on_normalCrossRedButton_clicked();
    void on_normalPendulumButton_clicked();
    void on_normalRenderGraph_clicked();
    void on_altBackEdgeButton_clicked();
    void on_altDummyNodesButton_clicked();
    void on_altCrossRedButton_clicked();
    void on_altPendulumButton_clicked();
};

#endif // MAINWINDOW_H
