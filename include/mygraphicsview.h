#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class MyGraphicsView : public QGraphicsView
{
public:
    explicit MyGraphicsView(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent* event);

};

#endif // MYGRAPHICSVIEW_H
