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
    const QString getName() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual ~BlockItem(){}

    QPointF getInport();
    QPointF getOutport();

private:
    QString name;
    int width;
    int height;

};

#endif // BLOCKITEM_H
