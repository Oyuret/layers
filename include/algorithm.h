#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QObject>
#include <QGraphicsScene>
#include "graph.h"

class Algorithm : public QObject
{
    Q_OBJECT
public:
    Algorithm();
    virtual void run(Graph& graph);
    virtual void run(Graph& graph, QGraphicsScene* scene);
    virtual ~Algorithm() {}

signals:
    void setStatusMsg(QString msg);
};

#endif // ALGORITHM_H
