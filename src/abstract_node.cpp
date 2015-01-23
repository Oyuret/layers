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

int AbstractNode::getPositionInLayer() const
{
    return positionInLayer;
}

void AbstractNode::setPositionInLayer(int position)
{
    positionInLayer = position;
}

double AbstractNode::getDownsweepWeight() const
{
    if(predecessors.size() == 0) {
        return getUpsweepWeight();
    }

    // sum the position of my predecessors
    int positions = 0;
    for(AbstractNode* predecessor : predecessors) {
        positions += predecessor->getPositionInLayer();
    }

    return (double) positions/predecessors.size();
}

double AbstractNode::getUpsweepWeight() const
{
    if(successors.size()== 0) {
        return getDownsweepWeight();
    }

    // sum the position of my successors
    int positions = 0;
    for(AbstractNode* successor : successors) {
        positions += successor->getPositionInLayer();
    }

    return (double) positions/successors.size();
}

const AbstractNode *AbstractNode::getFirstSucc() const
{
    return successors.first();
}

QList<AbstractNode *> &AbstractNode::getIbeds()
{
    return ibeds;
}

QList<AbstractNode *> &AbstractNode::getObeds()
{
    return obeds;
}

bool AbstractNode::isDummy() const
{
    return false;
}

bool AbstractNode::isIbed() const
{
    return false;
}

bool AbstractNode::isObed() const
{
    return false;
}
