#include "include/ibed.h"

Ibed::Ibed() :
    AbstractNode("ibed",10,10)
{
}

QRectF Ibed::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Ibed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setClipRect(option->exposedRect);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    painter->drawRoundedRect(0, 0, width, height, CORNER_RADIUS, CORNER_RADIUS);
}

QPointF Ibed::getInport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    position.setY(position.y() + (height/2));
    return position;
}

QPointF Ibed::getOutport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    position.setY(position.y() + (height/2));
    return position;
}

bool Ibed::isIbed() const
{
    return true;
}
