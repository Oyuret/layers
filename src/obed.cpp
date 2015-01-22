#include "include/obed.h"

Obed::Obed() :
    AbstractNode("obed",25,25)
{
}

QRectF Obed::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Obed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setClipRect(option->exposedRect);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRoundedRect(0, 0, width, height, CORNER_RADIUS, CORNER_RADIUS);
}

QPointF Obed::getInport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    position.setY(position.y() + (height/2));
    return position;
}

QPointF Obed::getOutport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    position.setY(position.y() + (height/2));
    return position;
}

bool Obed::isObed() const
{
    return true;
}
