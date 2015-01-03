#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QObject>
#include "graph.h"

class Algorithm : public QObject
{
    Q_OBJECT
public:
    Algorithm();
    virtual void run(Graph& graph);
    virtual ~Algorithm() {}

signals:
    void setStatusMsg(QString msg);
};

#endif // ALGORITHM_H
