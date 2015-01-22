#ifndef OBED_H
#define OBED_H
#include "abstract_node.h"

class Obed : public AbstractNode
{
public:
    Obed();
    virtual ~Obed(){}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QPointF getInport();
    virtual QPointF getOutport();
    virtual bool isObed() const;
};

#endif // OBED_H
