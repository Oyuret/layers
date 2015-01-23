#include "include/altreducecrossings.h"

AltReduceCrossings::AltReduceCrossings() :
    Algorithm()
{
}

void AltReduceCrossings::run(Graph &graph)
{
    emit setStatusMsg("Reducing crossings...");

    // set the position in layer for all nodes
    for(QList<AbstractNode*>& layer : graph.getLayers()) {
        int position =0;
        for(AbstractNode* node : layer) {
            node->setPositionInLayer(position);
            position++;
        }
    }

    // One iteration for each edge
    //int MAX_ITERATIONS = graph.getEdges().size() + graph.getReversedEdges().size();
    int MAX_ITERATIONS = 300;

    // initialize the crossing reduction
    for(int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
        downsweep(graph);
        upsweep(graph);
    }
    downsweep(graph);

    emit setStatusMsg("Reducing crossings...Done!");
}

void AltReduceCrossings::downsweep(Graph &graph)
{
    QList<QList<AbstractNode*>>& layers = graph.getLayers();

    for(int layer=1; layer<layers.size(); ++layer) {
        std::sort(layers[layer].begin(),layers[layer].end(),[](const AbstractNode* const x, const AbstractNode* const y){ return x->getDownsweepWeight() < y->getDownsweepWeight(); });

        // remove the ibeds from the layer
        QList<AbstractNode*> toRemove;
        for(AbstractNode* node : layers[layer]) {
            if(node->isIbed()) {
                toRemove.append(node);
            }
        }
        for(AbstractNode* removeItem : toRemove) {
            layers[layer].removeAll(removeItem);
        }

        // Replace the Ibeds
        QList<AbstractNode*> layersCpy = layers[layer];
        for(AbstractNode* node : layersCpy) {
            for(AbstractNode* ibed : node->getIbeds()) {
                layers[layer].insert(layers[layer].indexOf(node),ibed);
            }
        }

        // update the positionings now
        updatePositionings(layers[layer]);
    }


}

void AltReduceCrossings::upsweep(Graph &graph)
{
    QList<QList<AbstractNode*>>& layers = graph.getLayers();

    for(int layer=layers.size()-1; layer>=0; --layer) {
        std::sort(layers[layer].begin(),layers[layer].end(),[](const AbstractNode* const x, const AbstractNode* const y){ return x->getUpsweepWeight() < y->getUpsweepWeight(); });

        // remove the ibeds from the layer
        QList<AbstractNode*> toRemove;
        for(AbstractNode* node : layers[layer]) {
            if(node->isIbed()) {
                toRemove.append(node);
            }
        }
        for(AbstractNode* removeItem : toRemove) {
            layers[layer].removeAll(removeItem);
        }

        // Replace the Ibeds
        QList<AbstractNode*> layersCpy = layers[layer];
        for(AbstractNode* node : layersCpy) {
            for(AbstractNode* ibed : node->getIbeds()) {
                layers[layer].insert(layers[layer].indexOf(node),ibed);
            }
        }

        // update the positionings now
        updatePositionings(layers[layer]);
    }
}

void AltReduceCrossings::updatePositionings(QList<AbstractNode *> &layer)
{
    int position = 0;
    for(AbstractNode* node : layer) {
        node->setPositionInLayer(position);
        position++;
    }
}
