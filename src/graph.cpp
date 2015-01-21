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
    from->addSuccessor(to);
    to->addPredecessor(from);
}

void Graph::addReversedEdge(AbstractNode *from, AbstractNode *to, EdgeItem *edge)
{
    QPair<AbstractNode*,AbstractNode*> pair(from,to);
    reversedEdges.insert(pair,edge);
    from->addSuccessor(to);
    to->addPredecessor(from);
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

QList<EdgeItem *> Graph::getEdges()
{
    return edges.values();
}

EdgeItem *Graph::getReversedEdge(AbstractNode *from, AbstractNode *to)
{
    QPair<AbstractNode*, AbstractNode*> pair(from,to);
    return reversedEdges.value(pair);
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

    //add it to the set of reversed edges
    QPair<AbstractNode*, AbstractNode*> pairReversed(to,from);
    reversedEdges.insert(pairReversed,edge);
}

QList<EdgeItem *> Graph::getReversedEdges()
{
    return reversedEdges.values();
}

QList<EdgeItem *> Graph::findEdge(AbstractNode *from, AbstractNode *to)
{
    QPair<AbstractNode*, AbstractNode*> pair(from,to);
    QList<EdgeItem*> edgesList;

    if(edges.contains(pair)) {
        edgesList.append(edges.value(pair));
    }

    if(reversedEdges.contains(pair)) {
        edgesList.append(reversedEdges.value(pair));
    }

    return edgesList;
}

void Graph::setLayers(QList<QList<AbstractNode *> > layers)
{
    this->layers = layers;
}

QList<QList<AbstractNode *> > &Graph::getLayers()
{
    return layers;
}

void Graph::repaintLayers()
{
    qreal currentY(0);
    for(QList<AbstractNode*> layer : layers) {

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

void Graph::removeEdge(AbstractNode *from, AbstractNode *to)
{
    from->removeSuccessor(to);
    to->removePredecessor(from);
    QPair<AbstractNode*, AbstractNode*> toBeRemoved(from,to);
    edges.remove(toBeRemoved);
}

void Graph::removeReversedEdge(AbstractNode *from, AbstractNode *to)
{
    from->removeSuccessor(to);
    to->removePredecessor(from);
    QPair<AbstractNode*, AbstractNode*> toBeRemoved(from,to);
    reversedEdges.remove(toBeRemoved);
}

void Graph::adjustAllEdges()
{
    for(EdgeItem* edge : edges) {
        edge->adjust();
    }

    for(EdgeItem* edge : reversedEdges) {
        edge->adjust();
    }
}
