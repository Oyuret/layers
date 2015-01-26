#include "include/edgeitem.h"

EdgeItem::EdgeItem(AbstractNode *from, AbstractNode *to, bool renderArrow) :
    AbstractEdge(from,to),
    renderArrow(renderArrow),
    isIbedEdge(false)
{
}

QRectF EdgeItem::boundingRect() const
{
    return pathLine.boundingRect().united(arrow.boundingRect());
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setClipRect(option->exposedRect);
    if(!reversed) {
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::black);
    } else {
        painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::red);
    }




    painter->drawPath(pathLine.path());
    if(renderArrow) painter->drawPolygon(arrow);

}

void EdgeItem::adjust(bool cosmetically)
{
    prepareGeometryChange();

    QPointF sourcePoint;
    QPointF destinationPoint;

    if(cosmetically) {
        sourcePoint = from->getInport();
        destinationPoint = to->getOutport();
    } else {
        sourcePoint = from->getOutport();
        destinationPoint = to->getInport();
    }

    if(isIbedEdge) {
        destinationPoint = to->getIbedInport();
    }


    // add the bends to the path
    QPainterPath path;
    path.moveTo(sourcePoint);
    for(QPointF bend : bends) {
        path.lineTo(bend);
        path.moveTo(bend);
    }
    path.lineTo(destinationPoint);
    pathLine.setPath(path);

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
}

void EdgeItem::reverse(bool cosmetically)
{
    // update from/to
    AbstractNode* tmp = from;
    from = to;
    to = tmp;

    // reverse the order of the bends
    std::reverse(bends.begin(),bends.end());
    if(!cosmetically) {
        swapReversed();
    }

    // draw line?
    if(to->isDummy()) {
        renderArrow = false;
    } else {
        renderArrow = true;
    }

    if(cosmetically) {
        adjust(true);
    } else {
        adjust();
    }
}

void EdgeItem::addBend(QPointF bend)
{
    bends.append(bend);
}

void EdgeItem::setRenderArrow(bool render)
{
    this->renderArrow = render;
}

void EdgeItem::setIsIbedEdge(bool ibed)
{
    this->isIbedEdge = ibed;
}
