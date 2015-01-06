#ifndef DUMMYNODE_H
#define DUMMYNODE_H
#include "abstract_node.h"

class DummyNode : public AbstractNode
{
public:
    DummyNode();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual ~DummyNode() {}
};

#endif // DUMMYNODE_H
