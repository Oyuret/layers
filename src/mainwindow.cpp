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
    test.run();
}

void MainWindow::on_actionLoad_XML_triggered()
{
    scene->clear();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Files (*.xml)", NULL);
    CFG cfg = parser.getCFG(fileName);

    for(Block block : cfg.getBlocks()) {
        Node* node = new Node(block.getName());
        node->setX(qrand() % ((500 + 1) - (-500)) + (-500));
        node->setY(qrand() % ((500 + 1) - (-500)) + (-500));
        scene->addItem(node);
    }
}
