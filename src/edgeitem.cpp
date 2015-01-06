#include "include/edgeitem.h"

EdgeItem::EdgeItem(AbstractNode *from, AbstractNode *to, bool renderArrow) :
    AbstractEdge(from,to),
    renderArrow(renderArrow)
{
}

QRectF EdgeItem::boundingRect() const
{
    return line.boundingRect().united(arrow.boundingRect());
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setClipRect(option->exposedRect);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::black);


    painter->drawLine(line.line());
    if(renderArrow) painter->drawPolygon(arrow);

}

void EdgeItem::adjust()
{
    QPointF sourcePoint = from->getOutport();
    QPointF destinationPoint = to->getInport();

    //adjust the line
    /*points.clear();
    points.push_back(from->getOutport());
    for(QPointF point : bends) {
        points.push_back(point);
    }
    points.push_back(to->getInport());*/
    line.setLine(from->getOutport().x(),from->getOutport().y(),to->getInport().x(),to->getInport().y());

    // adjust the arrow
    if(renderArrow) {
        arrow.clear();

        // if it's not a straight line
        if(bends.size()!=0) {
            sourcePoint = bends.back();
        }

        QLineF arrowLine(sourcePoint, destinationPoint);
        double angle = ::acos(arrowLine.dx() / arrowLine.length());
        if (arrowLine.dy() >= 0) {
            angle = TwoPi - angle;
        }

        QPointF destArrowP1 = destinationPoint + QPointF(sin(angle - Pi / 3) * 10, cos(angle - Pi / 3) * 10);
        QPointF destArrowP2 = destinationPoint + QPointF(sin(angle - Pi + Pi / 3) * 10, cos(angle - Pi + Pi / 3) * 10);

        arrow << arrowLine.p2() << destArrowP1 << destArrowP2;
    }
    update();
}

void EdgeItem::reverse()
{
    AbstractNode* tmp = from;
    from = to;
    to = tmp;
    adjust();
}
