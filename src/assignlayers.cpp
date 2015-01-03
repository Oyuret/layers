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
    QLinkedList<QLinkedList<AbstractNode*>> layers;

    //add the first layer
    layers.append(QLinkedList<AbstractNode*>());
    while(!vertices.isEmpty()) {
        AbstractNode* selected = nullptr;
        for(AbstractNode* v : vertices) {
            if(Z.contains(v->getPredecessors().toSet())) {
                selected = v;
                break;
            }
        }

        if(selected != nullptr) {
            layers.last().append(selected);
            U.insert(selected);
            vertices.removeOne(selected);
        } else {
            layers.append(QLinkedList<AbstractNode*>());
            Z.unite(U);
        }
    }

    graph.setLayers(layers);
    graph.repaintLayers();
    emit setStatusMsg("Assigning layers... Done!");
}
