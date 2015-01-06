#include "include/dummynode.h"

DummyNode::DummyNode() :
    AbstractNode("dummy",25,25)
{
}

QRectF DummyNode::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void DummyNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setClipRect(option->exposedRect);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);
    painter->drawRoundedRect(0, 0, width, height, CORNER_RADIUS, CORNER_RADIUS);
}
