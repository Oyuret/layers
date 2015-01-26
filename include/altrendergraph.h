#ifndef ALTRENDERGRAPH_H
#define ALTRENDERGRAPH_H
#include <QGraphicsScene>
#include <algorithm>
#include "algorithm.h"
#include "edgeitem.h"
#include "abstract_node.h"

class AltRenderGraph : public Algorithm
{
public:
    AltRenderGraph();
    virtual ~AltRenderGraph(){}
    virtual void run(Graph& graph, QGraphicsScene* scene);

private:
    QGraphicsScene* scene;
    void addReversedEdge(AbstractNode* from, AbstractNode* to, Graph &graph);
    void assignIbedTracks(const QList<AbstractNode *> &layer, const QList<AbstractNode*>& upper, Graph &graph, int fromTrack);
    int assignObedTracks(const QList<AbstractNode *> &layer, Graph& graph);
    int assignTracks(const QList<AbstractNode *> &upper, Graph &graph, int fromTrack);
    void hungarian(QList<AbstractNode*>& nodes, Graph& graph);
};

#endif // ALTRENDERGRAPH_H
