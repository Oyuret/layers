#ifndef EDGEITEM_H
#define EDGEITEM_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <list>
#include <algorithm>
#include "abstract_edge.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static const double TwoPi = 2.0 * Pi;

class EdgeItem : public QGraphicsItem, public AbstractEdge
{
public:
    EdgeItem(AbstractNode* from, AbstractNode* to, bool renderArrow);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void adjust(bool cosmetically=false);
    void reverse(bool cosmetically=false);
    void addBend(QPointF bend);
    virtual ~EdgeItem(){}
private:
    QGraphicsPathItem pathLine;
    QPolygonF arrow;
    QVector<QPointF> bends;
    bool renderArrow;

};

#endif // EDGEITEM_H
