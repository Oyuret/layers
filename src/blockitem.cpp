#include "include/blockitem.h"
static const qreal CORNER_RADIUS = 4.0f;

BlockItem::BlockItem(QString name, int width, int height)
{
    this->name = name;
    this->width = width;
    this->height = height;
}

const QString BlockItem::getName() const
{
    return name;
}

QRectF BlockItem::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void BlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setClipRect(option->exposedRect);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);
    painter->drawRoundedRect(0, 0, width, height, CORNER_RADIUS, CORNER_RADIUS);

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(8);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(boundingRect().translated(2,5), name);
}

QPointF BlockItem::getInport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    return position;
}

QPointF BlockItem::getOutport()
{
    QPointF position = pos();
    position.setX(position.x() + (width/2));
    position.setY(position.y() + height);
    return position;
}
