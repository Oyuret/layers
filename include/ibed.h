#ifndef IBED_H
#define IBED_H
#include "abstract_node.h"

class Ibed : public AbstractNode
{
public:
    Ibed();
    virtual ~Ibed(){}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QPointF getInport();
    virtual QPointF getOutport();
    virtual bool isIbed() const;

};

#endif // IBED_H
