#ifndef INSERTDUMMYNODES_H
#define INSERTDUMMYNODES_H
#include "algorithm.h"
#include "abstract_node.h"
#include "dummynode.h"
#include "edgeitem.h"
#include "graph.h"

class InsertDummyNodes : public Algorithm
{
public:
    InsertDummyNodes();
    virtual void run(Graph &graph, QGraphicsScene* scene);
    virtual ~InsertDummyNodes() {}
private:
    void addDummies(QList<QList<AbstractNode*>>& layers, Graph& graph, QGraphicsScene* scene,QList<EdgeItem*> edges);
    void addReversedDummies(QList<QList<AbstractNode*>>& layers, Graph& graph, QGraphicsScene* scene,QList<EdgeItem*> edges);
};

#endif // INSERTDUMMYNODES_H
