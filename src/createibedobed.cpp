#include "include/createibedobed.h"

CreateIbedObed::CreateIbedObed() :
    Algorithm()
{
}

void CreateIbedObed::run(Graph &graph, QGraphicsScene *scene)
{
    emit setStatusMsg("Creating ibeds and obeds...");

    // Create all pairs of ibeds and obeds and link them
    QList<EdgeItem*> reversedEdges = graph.getReversedEdges();
    for(EdgeItem* reversed : reversedEdges) {
        AbstractNode* originalFrom = reversed->getTo();
        AbstractNode* originalTo = reversed->getFrom();

        Ibed* ibed = new Ibed();
        Obed* obed = new Obed();
        EdgeItem* edge = new EdgeItem(ibed,obed,false);
        edge->swapReversed();

        // Tell who spawned the obed and where we are pointing to.
        obed->setSpawnedBy(originalFrom);
        obed->setPointingAt(originalTo);

        // Add the ibeds to their owners
        originalTo->getIbeds().append(ibed);

        // add items to scene
        scene->addItem(ibed);
        scene->addItem(obed);
        scene->addItem(edge);

        // remove the old edge
        graph.removeReversedEdge(reversed->getFrom(),reversed->getTo());
        graph.addReversedEdge(ibed,obed,edge);
        scene->removeItem(reversed);

        // give the new nodes their layer
        ibed->setLayer(originalTo->getLayer());
        obed->setLayer(originalFrom->getLayer());

        // insert the obeds to their position
        QList<AbstractNode*>& obedLayer = graph.getLayers()[originalFrom->getLayer()];
        obedLayer.insert(obedLayer.indexOf(originalFrom),obed);
    }

    // Order all ibeds, reverse the list
    for(AbstractNode* node : graph.getNodes()) {
        std::sort(node->getIbeds().begin(),node->getIbeds().end(),[](const AbstractNode* const n1,
                  const AbstractNode* const n2){return n1->getFirstSucc()->getLayer()
                    < n2->getFirstSucc()->getLayer();});
        std::reverse(node->getIbeds().begin(),node->getIbeds().end());
    }

    // insert the ibeds to their layer
    for(AbstractNode* node : graph.getNodes()) {
        QList<AbstractNode*>& ibedLayer = graph.getLayers()[node->getLayer()];

        for(AbstractNode* ibed : node->getIbeds()) {
            ibedLayer.insert(ibedLayer.indexOf(node),ibed);
        }
    }

    emit setStatusMsg("Creating ibeds and obeds...Done!");
}
