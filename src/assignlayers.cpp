#include "include/assignlayers.h"
#include <QDebug>

AssignLayers::AssignLayers()
{
}

void AssignLayers::run(Graph &graph)
{
    emit setStatusMsg("Assigning layers...");

    // copy the nodes to a linked list
    QLinkedList<AbstractNode*> vertices;
    for(AbstractNode* v : graph.getNodes()) {
        vertices.append(v);
    }

    QSet<AbstractNode*> U;
    QSet<AbstractNode*> Z;
    QList<QList<AbstractNode*>> layers;

    //add the first layer
    int currentLayer = 0;
    layers.append(QList<AbstractNode*>());
    while(!vertices.isEmpty()) {
        AbstractNode* selected = nullptr;
        for(AbstractNode* v : vertices) {
            if(Z.contains(v->getPredecessors().toSet())) {
                selected = v;
                break;
            }
        }

        if(selected != nullptr) {
            selected->setLayer(currentLayer);
            layers.last().append(selected);
            U.insert(selected);
            vertices.removeOne(selected);
        } else {
            currentLayer++;
            layers.append(QList<AbstractNode*>());
            Z.unite(U);
        }
    }

    graph.setLayers(layers);
    graph.repaintLayers();
    emit setStatusMsg("Assigning layers... Done!");
}
