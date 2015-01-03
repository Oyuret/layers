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

list<AbstractNode *> &AbstractNode::getSuccessors()
{
    return successors;
}

list<AbstractNode *> &AbstractNode::getPredecessors()
{
    return predecessors;
}

void AbstractNode::removePredecessor(AbstractNode *node)
{
    predecessors.remove(node);
}

void AbstractNode::removeSuccessor(AbstractNode *node)
{
    successors.remove(node);
}
