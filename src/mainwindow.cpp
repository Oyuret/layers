#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    connect(&removeCycles,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));
    connect(&parser,SIGNAL(setStatusMsg(QString)),this,SLOT(on_setStatusMsg(QString)));

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


    // add all successors
    for(Block block : cfg.getBlocks()) {
        AbstractNode* node = graph.getNode(block.getName());
        for(QString succ : block.getSuccessors()) {
            AbstractNode* successor = graph.getNode(succ);
            node->addSuccessor(successor);
        }
    }

    // add all predecessors
    for(Block block : cfg.getBlocks()) {
        AbstractNode* node = graph.getNode(block.getName());
        for(QString pred : block.getPredecessors()) {
            AbstractNode* predecessor = graph.getNode(pred);
            node->addPredecessor(predecessor);
        }
    }

    // add all edges
    for(AbstractNode* node : graph.getNodes()) {
        for(AbstractNode* successor: node->getSuccessors()) {
           EdgeItem* edge = new EdgeItem(node,successor,true);
           edge->adjust();
           scene->addItem(edge);
           graph.addEdge(node,successor,edge);
        }
    }

    graph.setStart(graph.getNode(cfg.getStart().getName()));
}
