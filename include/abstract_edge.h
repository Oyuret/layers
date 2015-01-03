#ifndef ABSTRACTEDGE_H
#define ABSTRACTEDGE_H
#include "abstract_node.h"

class AbstractEdge
{
public:
    AbstractEdge();
    AbstractEdge(AbstractNode* from, AbstractNode* to);
    AbstractNode* getFrom() {return from;}
    AbstractNode* getTo() {return to;}
    virtual ~AbstractEdge(){}
protected:
    AbstractNode* from;
    AbstractNode* to;
};

#endif // ABSTRACTEDGE_H
