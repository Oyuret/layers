#include "include/dummynode.h"

DummyNode::DummyNode() :
    AbstractNode("dummy",10,10)
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

QPointF DummyNode::getInport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    position.setY(position.y() + (height/2));
    return position;
}

QPointF DummyNode::getOutport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    position.setY(position.y() + (height/2));
    return position;
}

bool DummyNode::isDummy() const
{
    return true;
}
