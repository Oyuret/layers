#ifndef ALTRENDERGRAPH_H
#define ALTRENDERGRAPH_H
#include "algorithm.h"

class AltRenderGraph : public Algorithm
{
public:
    AltRenderGraph();
    virtual ~AltRenderGraph(){}
    virtual void run(Graph& graph);

private:
    void assignIbedTracks(int fromTrack);
    void assignObedTracks(int fromTrack);
    int assignTracks(const QList<AbstractNode *> &upper, const QList<AbstractNode *> &lower, Graph &graph, int fromTrack);
};

#endif // ALTRENDERGRAPH_H
