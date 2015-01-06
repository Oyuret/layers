#include "include/abstract_node.h"

AbstractNode::AbstractNode()
{
}

AbstractNode::AbstractNode(QString name, int width, int height) :
    BlockItem(name, width, height)
{

}

void AbstractNode::addSuccessor(AbstractNode *successor)
{
    successors.push_back(successor);
}

void AbstractNode::addPredecessor(AbstractNode *predecessor)
{
    predecessors.push_back(predecessor);
}

QList<AbstractNode *> &AbstractNode::getSuccessors()
{
    return successors;
}

QList<AbstractNode *> &AbstractNode::getPredecessors()
{
    return predecessors;
}

void AbstractNode::removePredecessor(AbstractNode *node)
{
    predecessors.removeOne(node);
}

void AbstractNode::removeSuccessor(AbstractNode *node)
{
    successors.removeOne(node);
}

void AbstractNode::setLayer(int layer)
{
    this->layer = layer;
}

int AbstractNode::getLayer() const
{
    return layer;
}
