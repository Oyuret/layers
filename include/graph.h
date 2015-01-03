#ifndef GRAPH_H
#define GRAPH_H
#include <QMap>
#include <QLinkedList>
#include "abstract_node.h"
#include "edgeitem.h"

using namespace std;

class Graph
{
public:
    Graph();
    void addNode(AbstractNode* node);
    void addEdge(AbstractNode* from, AbstractNode* to, EdgeItem* edge);
    void setStart(AbstractNode* node);

    AbstractNode* getNode(QString name);
    QList<AbstractNode*> getNodes();
    AbstractNode* getStart();
    EdgeItem* getEdge(AbstractNode* from, AbstractNode* to);

    void reverseEdge(AbstractNode* from, AbstractNode* to);
    QList<EdgeItem *> getReversedEdges();


    void setLayers(QLinkedList<QLinkedList<AbstractNode*>> layers);
    void repaintLayers();

    void clear();
    void resetReversed();
    virtual ~Graph(){}

private:
    void adjustAllEdges();


    AbstractNode* start;
    QMap<QString,AbstractNode*> nodes;
    QLinkedList<QLinkedList<AbstractNode*>> layers;
    QMap<QPair<AbstractNode*,AbstractNode*>,EdgeItem*> edges;
    QMap<QPair<AbstractNode*,AbstractNode*>,EdgeItem*> reversedEdges;

};

#endif // GRAPH_H
