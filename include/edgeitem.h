#ifndef EDGEITEM_H
#define EDGEITEM_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <list>
#include "abstract_edge.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static const double TwoPi = 2.0 * Pi;

class EdgeItem : public QGraphicsItem, public AbstractEdge
{
public:
    EdgeItem(AbstractNode* from, AbstractNode* to, bool renderArrow);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void adjust();
    void reverse();
    virtual ~EdgeItem(){}
private:
    QPolygonF arrow;
    QVector<QPointF> bends;
    QVector<QPointF> points;
    bool renderArrow;

};

#endif // EDGEITEM_H
