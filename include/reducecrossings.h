#ifndef REDUCECROSSINGS_H
#define REDUCECROSSINGS_H

#include <algorithm>
#include "algorithm.h"
#include "graph.h"
#include "abstract_node.h"

class ReduceCrossings : public Algorithm
{
public:
    ReduceCrossings();
    virtual ~ReduceCrossings(){}
    virtual void run(Graph& graph);
private:
    void downsweep(Graph& graph);
    void upsweep(Graph& graph);
    int calculateCrossings(Graph& graph);
    void updatePositionings(QList<AbstractNode *> &layer);
};

#endif // REDUCECROSSINGS_H
