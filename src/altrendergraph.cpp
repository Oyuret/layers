#include "include/altrendergraph.h"
#include <QDebug>

AltRenderGraph::AltRenderGraph() :
    Algorithm()
{
}

void AltRenderGraph::run(Graph &graph, QGraphicsScene *scene)
{
    emit setStatusMsg("Rendering graph...");
    this->scene = scene;


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

    // handle first layers ibeds
    assignIbedTracks(graph.getLayers().first(), graph,0);

    // handle all other layers
    for(int i=0; i<graph.getLayers().size()-1; ++i) {
        int fromTrack;
        fromTrack = assignObedTracks(graph.getLayers().at(i), graph);
        fromTrack = assignTracks(graph.getLayers().at(i),graph.getLayers().at(i+1),graph, fromTrack);
        assignIbedTracks(graph.getLayers().at(i+1),graph, fromTrack);
    }

    // handle last obed tracks
    assignObedTracks(graph.getLayers().last(), graph);


    graph.adjustAllEdges();



    emit setStatusMsg("Rendering graph...Done!");
}

void AltRenderGraph::addReversedEdge(AbstractNode *from, AbstractNode *to, Graph& graph)
{
    // add the new edge to the graph
    EdgeItem* edge = new EdgeItem(from,to,true);
    edge->swapReversed();
    graph.addReversedEdge(from,to,edge);
    scene->addItem(edge);
}

void AltRenderGraph::assignIbedTracks(const QList<AbstractNode*>& layer, Graph& graph, int fromTrack)
{
    // Add a reversed edge from each ibed to its father
    for(AbstractNode* node : layer) {
        for(AbstractNode* ibed : node->getIbeds()) {
            addReversedEdge(ibed,node,graph);
        }
    }
}

int AltRenderGraph::assignObedTracks(const QList<AbstractNode *> &layer, Graph &graph)
{

    // Get all the destinations in this layer
    QList<AbstractNode*> destinations;
    for(AbstractNode* node : layer) {
        if(node->isObed()) {
            if(destinations.contains(node->getPointingAt())) {
                continue;
            }
            destinations.append(node->getPointingAt());
        }
    }

    // Pair up obeds to nodes
    for(AbstractNode* destination : destinations) {
        QList<AbstractNode*> hungarianList;

        for(AbstractNode* node : layer) {
            if(node->isObed()) {

                if(node->getPointingAt() != destination) {
                    continue;
                }

                hungarianList.append(node);
                hungarianList.append(node->getSpawnedBy());
            }
        }
        hungarian(hungarianList,graph);
    }

    // Assign tracks now

    return 0;
}

int AltRenderGraph::assignTracks(const QList<AbstractNode *> &upper, const QList<AbstractNode *> &lower, Graph &graph, int fromTrack)
{
    return 0;

}

void AltRenderGraph::hungarian(QList<AbstractNode *> &nodes, Graph &graph)
{
    // order the list by position in layer
    std::sort(nodes.begin(),nodes.end(),[](const AbstractNode* const n1, const AbstractNode* const n2){return n1->getPositionInLayer() < n2->getPositionInLayer();});

    while(!nodes.isEmpty()) {

        // split nodes into obeds and normal nodes
        QList<AbstractNode*> obeds;
        QList<AbstractNode*> normalNodes;

        for(AbstractNode* node : nodes) {
            if(node->isObed()) {
                obeds.append(node);
            } else {
                normalNodes.append(node);
            }
        }

        // calculate distance from each obed to each node
        for(AbstractNode* obed : obeds) {
            QList<int> distances;
            QMap<int,AbstractNode*> distanceMap;
            for(AbstractNode* normal : normalNodes) {
                int distance = abs(nodes.indexOf(normal)-nodes.indexOf(obed));
                distances.append(distance);
                distanceMap.insert(distance,normal);
            }

            // if only one normal node is at distance 1 of us pair us up
            if(distances.count(1) == 1) {
                AbstractNode * from = distanceMap.value(1);
                addReversedEdge(from,obed,graph);
                nodes.removeAll(obed);
                nodes.removeAll(from);
                break;
            }
        }


    }


}
