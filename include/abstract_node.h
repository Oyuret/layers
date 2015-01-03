#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H
#include <list>
#include "blockitem.h"

using namespace std;

class AbstractNode : public BlockItem
{
public:
    AbstractNode();
    AbstractNode(QString name, int width, int height);
    void addSuccessor(AbstractNode* successor);
    void addPredecessor(AbstractNode* predecessor);
    list<AbstractNode*>& getSuccessors();
    list<AbstractNode*>& getPredecessors();
    void removePredecessor(AbstractNode* node);
    void removeSuccessor(AbstractNode* node);
    virtual ~AbstractNode(){}

private:
    list<AbstractNode*> successors;
    list<AbstractNode*> predecessors;
};

#endif // ABSTRACTNODE_H
