#include "include/abstract_node.h"

AbstractNode::AbstractNode()
{
}

list<AbstractNode *> &AbstractNode::getSuccessors()
{
    return successors;
}

list<AbstractNode *> &AbstractNode::getPredecessors()
{
    return predecessors;
}
