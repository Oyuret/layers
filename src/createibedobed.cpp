#include "include/createibedobed.h"

CreateIbedObed::CreateIbedObed() :
    Algorithm()
{
}

void CreateIbedObed::run(Graph &graph, QGraphicsScene *scene)
{
    emit setStatusMsg("Creating ibeds and obeds...");

    // Create all pairs and link them
    QList<EdgeItem*> reversedEdges = graph.getReversedEdges();
    for(EdgeItem* reversed : reversedEdges) {
        AbstractNode* originalFrom = reversed->getTo();
        AbstractNode* originalTo = reversed->getFrom();

        Ibed* ibed = new Ibed();
        Obed* obed = new Obed();
        EdgeItem* ibedObedEdge = new EdgeItem(ibed,obed,false);
        ibedObedEdge->swapReversed();

        scene->addItem(ibed);
        scene->addItem(obed);
        scene->addItem(ibedObedEdge);

        graph.removeReversedEdge(reversed->getFrom(),reversed->getTo());
        graph.addReversedEdge(ibed,obed,ibedObedEdge);
        scene->removeItem(reversed);

        // place in layers
        QList<AbstractNode*>& ibedLayer = graph.getLayers()[originalTo->getLayer()];
        ibedLayer.insert(ibedLayer.indexOf(originalTo),ibed);
        ibed->setLayer(originalTo->getLayer());

        QList<AbstractNode*>& obedLayer = graph.getLayers()[originalFrom->getLayer()];
        obedLayer.insert(obedLayer.indexOf(originalFrom),obed);
        obed->setLayer(originalFrom->getLayer());

    }

    //  TODO: order ibeds by layer

    emit setStatusMsg("Creating ibeds and obeds...Done!");
}
