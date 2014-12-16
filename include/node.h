#ifndef NODE_H
#define NODE_H
#include "abstract_node.h"
#include "blockitem.h"

class Node : public BlockItem, AbstractNode
{
public:
    Node(QString name);
    virtual ~Node(){}

};

#endif // NODE_H
