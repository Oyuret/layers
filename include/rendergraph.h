#ifndef RENDERGRAPH_H
#define RENDERGRAPH_H
#include "algorithm.h"
#include <algorithm>

class RenderGraph : public Algorithm
{
public:
    RenderGraph();
    virtual void run(Graph& graph);
    virtual ~RenderGraph(){}

private:
    void assignTracks(const QList<AbstractNode *> &upper, const QList<AbstractNode *> &lower, Graph &graph);
};

#endif // RENDERGRAPH_H
