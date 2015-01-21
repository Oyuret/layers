#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>

class BlockItem : public QGraphicsItem
{
public:
    BlockItem(){}
    BlockItem(QString name, int width, int height);
    void changeName(QString name);
    const QString getName() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual ~BlockItem(){}

    virtual QPointF getInport();
    virtual QPointF getOutport();

protected:
    QString name;
    int width;
    int height;
    const qreal CORNER_RADIUS = 4.0f;

};

#endif // BLOCKITEM_H
