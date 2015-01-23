#include "include/altrendergraph.h"

AltRenderGraph::AltRenderGraph() :
    Algorithm()
{
}

void AltRenderGraph::run(Graph &graph)
{
    emit setStatusMsg("Rendering graph...");


    // Center all nodes along the y-axis
    for(const QList<AbstractNode*>& layer : graph.getLayers() ) {

        qreal maxHeight = layer.first()->boundingRect().height();
        for(AbstractNode* n : layer) {
            maxHeight = std::max(n->boundingRect().height(),maxHeight);
        }

        for(AbstractNode* n : layer) {
            qreal offset = (maxHeight - n->boundingRect().height())/2;
            n->setY(n->y()+offset);
        }
    }

    graph.adjustAllEdges();



    emit setStatusMsg("Rendering graph...Done!");
}

void AltRenderGraph::assignIbedTracks(int fromTrack)
{

}

void AltRenderGraph::assignObedTracks(int fromTrack)
{

}

int AltRenderGraph::assignTracks(const QList<AbstractNode *> &upper, const QList<AbstractNode *> &lower, Graph &graph, int fromTrack)
{
    return 0;

}
