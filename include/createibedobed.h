#ifndef CREATEIBEDOBED_H
#define CREATEIBEDOBED_H
#include <QGraphicsScene>
#include <algorithm>
#include "algorithm.h"
#include "graph.h"
#include "edgeitem.h"
#include "ibed.h"
#include "obed.h"

class CreateIbedObed : public Algorithm
{
public:
    CreateIbedObed();
    virtual ~CreateIbedObed(){}

    virtual void run(Graph& graph, QGraphicsScene* scene);
};

#endif // CREATEIBEDOBED_H
