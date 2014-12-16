#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H
#include <list>

using namespace std;

class AbstractNode
{
public:
    AbstractNode();
    list<AbstractNode*>& getSuccessors();
    list<AbstractNode*>& getPredecessors();
    virtual ~AbstractNode(){}

private:
    list<AbstractNode*> successors;
    list<AbstractNode*> predecessors;
};

#endif // ABSTRACTNODE_H
