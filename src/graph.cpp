#include "include/graph.h"

Graph::Graph()
{
}

void Graph::addNode(AbstractNode *node)
{
    nodes.insert(node->getName(),node);
}

void Graph::addEdge(AbstractNode *from, AbstractNode *to, EdgeItem *edge)
{
    QPair<AbstractNode*,AbstractNode*> pair(from,to);
    edges.insert(pair,edge);
}

void Graph::setStart(AbstractNode *node)
{
    start = node;
}

AbstractNode *Graph::getNode(QString name)
{
    return nodes.value(name);
}

QList<AbstractNode*> Graph::getNodes()
{
    return nodes.values();
}

AbstractNode *Graph::getStart()
{
    return start;
}

EdgeItem *Graph::getEdge(AbstractNode *from, AbstractNode *to)
{
    QPair<AbstractNode*, AbstractNode*> pair(from,to);
    return edges.value(pair);
}

void Graph::reverseEdge(AbstractNode *from, AbstractNode *to)
{
    from->removeSuccessor(to);
    to->removePredecessor(from);
    from->addPredecessor(to);
    to->addSuccessor(from);

    QPair<AbstractNode*, AbstractNode*> pair(from,to);
    EdgeItem* edge = edges.value(pair);
    edge->reverse();
    edges.remove(pair);
    addEdge(to,from,edge);

    //add it to the set of reversed edges
    QPair<AbstractNode*, AbstractNode*> pairReversed(to,from);
    reversedEdges.insert(pairReversed,edge);
}

QList<EdgeItem *> Graph::getReversedEdges()
{
    return reversedEdges.values();
}

void Graph::clear()
{
    nodes.clear();
    layers.clear();
}

void Graph::resetReversed()
{
    reversedEdges.clear();
}
