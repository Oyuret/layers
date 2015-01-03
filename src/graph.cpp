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

void Graph::setLayers(QLinkedList<QLinkedList<AbstractNode *> > layers)
{
    this->layers = layers;
}

void Graph::repaintLayers()
{
    qreal currentY(0);
    for(QLinkedList<AbstractNode*> layer : layers) {

        qreal currentX(0);
        qreal maxHeightThisLayer(0);

        for(AbstractNode* vertex : layer) {

            // adjust the Y-position
            vertex->setY(currentY);
            if(maxHeightThisLayer < vertex->boundingRect().height()) {
                maxHeightThisLayer = vertex->boundingRect().height();
            }

            // adjust the X-position
            vertex->setX(currentX);
            currentX = currentX + vertex->boundingRect().width() + 25;
        }
        currentY = currentY + maxHeightThisLayer + 25;
    }

    adjustAllEdges();
}

void Graph::clear()
{
    nodes.clear();
    layers.clear();
    edges.clear();
    reversedEdges.clear();
}

void Graph::resetReversed()
{
    reversedEdges.clear();
}

void Graph::adjustAllEdges()
{
    for(EdgeItem* edge : edges) {
        edge->adjust();
    }
}
