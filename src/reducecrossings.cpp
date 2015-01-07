#include "include/reducecrossings.h"

ReduceCrossings::ReduceCrossings() :
    Algorithm()
{
}

void ReduceCrossings::run(Graph &graph)
{
    emit setStatusMsg("Reducing crossings...");
    int currentCrossings = INT_MAX;

    // set the position in layer for all nodes
    for(QList<AbstractNode*>& layer : graph.getLayers()) {
        int position =0;
        for(AbstractNode* node : layer) {
            node->setPositionInLayer(position);
            position++;
        }
    }

    // One iteration for each edge
    int MAX_ITERATIONS = graph.getEdges().size() + graph.getReversedEdges().size();

    // initialize the crossing reduction
    for(int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
        currentCrossings = calculateCrossings(graph);

        /*if(currentCrossings == 0) {
            break;
        }*/

        downsweep(graph);
        upsweep(graph);

    }

    emit setStatusMsg("Reducing crossings...Done!");
}

void ReduceCrossings::downsweep(Graph &graph)
{
    QList<QList<AbstractNode*>>& layers = graph.getLayers();

    for(int layer=1; layer<layers.size(); ++layer) {
        std::sort(layers[layer].begin(),layers[layer].end(),[](const AbstractNode* const x, const AbstractNode* const y){ return x->getDownsweepWeight() < y->getDownsweepWeight(); });
        updatePositionings(layers[layer]);
    }
}

void ReduceCrossings::upsweep(Graph &graph)
{
    QList<QList<AbstractNode*>>& layers = graph.getLayers();

    for(int layer=layers.size()-1; layer>=0; --layer) {
        std::sort(layers[layer].begin(),layers[layer].end(),[](const AbstractNode* const x, const AbstractNode* const y){ return x->getUpsweepWeight() < y->getUpsweepWeight(); });
        updatePositionings(layers[layer]);
    }

}

int ReduceCrossings::calculateCrossings(Graph &graph)
{
    Q_UNUSED(graph)
    return 0;
}

void ReduceCrossings::updatePositionings(QList<AbstractNode *>& layer)
{
    int position = 0;
    for(AbstractNode* node : layer) {
        node->setPositionInLayer(position);
        position++;
    }
}
