#ifndef NODE_H
#define NODE_H
#include "abstract_node.h"

class Node : public AbstractNode
{
public:
    Node(QString name, int width, int height);
    virtual ~Node(){}

};

#endif // NODE_H
