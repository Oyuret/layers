#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    // Normal algorithms
    connect(&removeCycles,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));
    connect(&assignLayers,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));
    connect(&insertDummyNodes,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));
    connect(&reduceCrossings,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));
    connect(&balanceGraph,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));
    connect(&renderGraph,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));
    connect(&parser,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));

    // Altered algorithms
    connect(&createIbedObed,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));

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
    removeCycles.run(graph);
}

void MainWindow::on_actionLoad_XML_triggered()
{
    scene->clear();
    graph.clear();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Files (*.xml)", NULL);
    CFG cfg = parser.getCFG(fileName);

    // add all blocks
    for(Block block : cfg.getBlocks()) {
        Node* node = new Node(block.getName(), 50, 50);
        node->setX(qrand() % ((500 + 1) - (-500)) + (-500));
        node->setY(qrand() % ((500 + 1) - (-500)) + (-500));
        scene->addItem(node);
        graph.addNode(node);
    }

    // add all edges
    for(Block block : cfg.getBlocks()) {
        AbstractNode* from = graph.getNode(block.getName());
        for(QString succName : block.getSuccessors()) {
            AbstractNode* to = graph.getNode(succName);
            EdgeItem* edge = new EdgeItem(from,to,true);
            edge->adjust();
            scene->addItem(edge);
            graph.addEdge(from,to,edge);
        }
    }

    graph.setStart(graph.getNode(cfg.getStart().getName()));
}

void MainWindow::on_layeringButton_clicked()
{
    assignLayers.run(graph);
}

void MainWindow::on_normalDummyNodesButton_clicked()
{
    insertDummyNodes.run(graph,scene);
    graph.repaintLayers();
    scene->update(scene->sceneRect());
}

void MainWindow::on_normalCrossRedButton_clicked()
{
    reduceCrossings.run(graph);
    graph.repaintLayers();
    scene->update(scene->sceneRect());
}

void MainWindow::on_normalPendulumButton_clicked()
{
    balanceGraph.run(graph);
    graph.adjustAllEdges();
    scene->update(scene->sceneRect());
}

void MainWindow::on_normalRenderGraph_clicked()
{
    renderGraph.run(graph);
    scene->update(scene->sceneRect());
}

void MainWindow::on_altBackEdgeButton_clicked()
{
    createIbedObed.run(graph,scene);
    graph.repaintLayers();
    scene->update(scene->sceneRect());
}

void MainWindow::on_altDummyNodesButton_clicked()
{
    insertDummyNodes.run(graph,scene);
    graph.repaintLayers();
    scene->update(scene->sceneRect());
}

void MainWindow::on_altCrossRedButton_clicked()
{
    altReduceCrossings.run(graph);
    graph.repaintLayers();
    scene->update(scene->sceneRect());
}

void MainWindow::on_altPendulumButton_clicked()
{
    balanceGraph.run(graph);
    graph.adjustAllEdges();
    scene->update(scene->sceneRect());
}
