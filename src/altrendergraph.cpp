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
    assignIbedTracks(graph.getLayers().first(),graph.getLayers().first(), graph,-1);

    // handle all other layers
    for(int i=0; i<graph.getLayers().size()-1; ++i) {
        int fromTrack = assignObedTracks(graph.getLayers().at(i), graph);
        fromTrack = assignTracks(graph.getLayers().at(i),graph, fromTrack);
        assignIbedTracks(graph.getLayers().at(i+1),graph.getLayers().at(i),graph, fromTrack);
    }

    // handle last obed tracks
    assignObedTracks(graph.getLayers().last(), graph);


    graph.adjustAllEdges();

    for(QList<AbstractNode*>& layer : graph.getLayers()){
        for(AbstractNode* node : layer) {
            if(node->isDummy() || node->isObed() || node->isIbed()) {
                node->hide();
            }
        }
    }

    for(EdgeItem* edge : graph.getReversedEdges()) {
        if(edge->getTo()->isObed() || edge->getTo()->isIbed()) {
            edge->setRenderArrow(false);
        }
    }


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

void AltRenderGraph::assignIbedTracks(const QList<AbstractNode*>& layer, const QList<AbstractNode*>& upper, Graph& graph, int fromTrack)
{
    // Add a reversed edge from each ibed to its father
    for(AbstractNode* node : layer) {
        for(AbstractNode* ibed : node->getIbeds()) {
            addReversedEdge(ibed,node,graph);
        }
    }

    // Add all edges to the timeline
    QList<QPair<qreal,EdgeItem*>> timeLine;
    for(AbstractNode* from : layer) {
        for(AbstractNode* to : from->getSuccessors()) {
            EdgeItem* edge = graph.getReversedEdge(from,to);

            if(!edge) {
                continue;
            }

            if(!edge->getFrom()->isIbed()) {
                continue;
            }

            if(edge->getFrom()->getOutport().x() == edge->getTo()->getInport().x()) {
                continue;
            }

            if(qAbs(edge->getFrom()->getOutport().x() - edge->getTo()->getInport().x()) < 2 ) {
                continue;
            }

            qreal startPosition(from->getOutport().x());
            qreal endPosition(to->getInport().x());

            QPair<qreal,EdgeItem*> start(startPosition,edge);
            QPair<qreal,EdgeItem*> end(endPosition,edge);

            if(!timeLine.contains(start)) {
                timeLine.append(start);
            }
            if(!timeLine.contains(end)) {
                timeLine.append(end);
            }
        }
    }
    std::sort(timeLine.begin(),timeLine.end(),[](const QPair<qreal,EdgeItem*>& p1,
              const QPair<qreal,EdgeItem*>& p2){return p1.first < p2.first;});

    int nrUsedTracks = 0;
    QMap<EdgeItem*,int> takenTracks;
    QMap<EdgeItem*,int> assignedTracks;
    for(QPair<qreal,EdgeItem*> edge : timeLine) {

        // if we already got that edge. Remove it from the taken tracks
        if(takenTracks.contains(edge.second)) {
            takenTracks.remove(edge.second);
            continue;
        } else {
            takenTracks.insert(edge.second,0);
            assignedTracks.insert(edge.second,nrUsedTracks);
            nrUsedTracks++;
        }

    }


    // Add bends
    qreal lowestPoint;
    if(fromTrack == -1) {
        lowestPoint = 0;
    } else {
        lowestPoint = upper.first()->y() + upper.first()->boundingRect().height();
        for(AbstractNode* node : upper) {
            lowestPoint = std::max(lowestPoint, node->y() + node->boundingRect().height());
        }
        lowestPoint = lowestPoint + 35 + fromTrack*15;
    }


    for(EdgeItem* edge : assignedTracks.keys()) {
        qreal trackPos = lowestPoint + (15*assignedTracks.value(edge));
        QPointF first(edge->getFrom()->getOutport().x(),trackPos);
        QPointF second(edge->getTo()->getInport().x(),trackPos);
        edge->addBend(first);
        edge->addBend(second);
    }

    qreal toMove = lowestPoint + nrUsedTracks*15 + 35;
    for(AbstractNode* node : layer) {
        node->setY(toMove);
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
    // Add all edges to the timeline
    QList<QPair<qreal,EdgeItem*>> timeLine;
    for(AbstractNode* from : layer) {
        for(AbstractNode* to : from->getSuccessors()) {
            EdgeItem* edge = graph.getReversedEdge(from,to);

            if(!edge) {
                continue;
            }

            if(!edge->getTo()->isObed()) {
                continue;
            }

            if(edge->getFrom()->getOutport().x() == edge->getTo()->getInport().x()) {
                continue;
            }

            if(qAbs(edge->getFrom()->getOutport().x() - edge->getTo()->getInport().x()) < 2 ) {
                continue;
            }

            qreal startPosition(from->getOutport().x());
            qreal endPosition(to->getInport().x());

            QPair<qreal,EdgeItem*> start(startPosition,edge);
            QPair<qreal,EdgeItem*> end(endPosition,edge);

            if(!timeLine.contains(start)) {
                timeLine.append(start);
            }
            if(!timeLine.contains(end)) {
                timeLine.append(end);
            }
        }
    }
    std::sort(timeLine.begin(),timeLine.end(),[](const QPair<qreal,EdgeItem*>& p1,
              const QPair<qreal,EdgeItem*>& p2){return p1.first < p2.first;});

    int nrUsedTracks = 0;
    QMap<EdgeItem*,int> takenTracks;
    QMap<EdgeItem*,int> assignedTracks;
    for(QPair<qreal,EdgeItem*> edge : timeLine) {

        // if we already got that edge. Remove it from the taken tracks
        if(takenTracks.contains(edge.second)) {
            takenTracks.remove(edge.second);
            continue;
        } else {
            takenTracks.insert(edge.second,0);
            assignedTracks.insert(edge.second,nrUsedTracks);
            nrUsedTracks++;
        }

    }


    // Add bends
    qreal lowestPoint = layer.first()->y() + layer.first()->boundingRect().height();
    for(AbstractNode* node : layer) {
        lowestPoint = std::max(lowestPoint, node->y() + node->boundingRect().height());
    }
    lowestPoint = lowestPoint + 35;

    // create inverted tracks
    QList<int> inverted;
    for(int i=0; i< nrUsedTracks; ++i) {
        inverted.append(i);
    }
    std::reverse(inverted.begin(),inverted.end());

    for(EdgeItem* edge : assignedTracks.keys()) {
        qreal trackPos = lowestPoint + (15*inverted.at(assignedTracks.value(edge)));
        QPointF first(edge->getFrom()->getOutport().x(),trackPos);
        QPointF second(edge->getTo()->getInport().x(),trackPos);
        edge->addBend(first);
        edge->addBend(second);
    }

    return nrUsedTracks;
}

int AltRenderGraph::assignTracks(const QList<AbstractNode *> &upper, Graph &graph, int fromTrack)
{
    // Add all edges to the timeline
    QList<QPair<qreal,EdgeItem*>> timeLine;
    for(AbstractNode* from : upper) {
        for(AbstractNode* to : from->getSuccessors()) {
            EdgeItem* edge = graph.getEdge(from,to);

            if(!edge) {
                continue;
            }

            if(edge->getFrom()->getOutport().x() == edge->getTo()->getInport().x()) {
                continue;
            }

            if(qAbs(edge->getFrom()->getOutport().x() - edge->getTo()->getInport().x()) < 2 ) {
                continue;
            }

            qreal startPosition(from->getOutport().x());
            qreal endPosition(to->getInport().x());

            QPair<qreal,EdgeItem*> start(startPosition,edge);
            QPair<qreal,EdgeItem*> end(endPosition,edge);

            if(!timeLine.contains(start)) {
                timeLine.append(start);
            }
            if(!timeLine.contains(end)) {
                timeLine.append(end);
            }
        }
    }
    std::sort(timeLine.begin(),timeLine.end(),[](const QPair<qreal,EdgeItem*>& p1,
              const QPair<qreal,EdgeItem*>& p2){return p1.first < p2.first;});

    int nrUsedTracks = 0;
    QMap<EdgeItem*,int> takenTracks;
    QMap<EdgeItem*,int> assignedTracks;
    for(QPair<qreal,EdgeItem*> edge : timeLine) {

        // if we already got that edge. Remove it from the taken tracks
        if(takenTracks.contains(edge.second)) {
            takenTracks.remove(edge.second);
            continue;
        } else {
            takenTracks.insert(edge.second,0);
            assignedTracks.insert(edge.second,nrUsedTracks);
            nrUsedTracks++;
        }

    }


    // Add bends
    qreal lowestPoint = upper.first()->y() + upper.first()->boundingRect().height();
    for(AbstractNode* node : upper) {
        lowestPoint = std::max(lowestPoint, node->y() + node->boundingRect().height());
    }
    lowestPoint = lowestPoint + 35 + fromTrack*15;

    for(EdgeItem* edge : assignedTracks.keys()) {
        qreal trackPos = lowestPoint + (15*assignedTracks.value(edge));
        QPointF first(edge->getFrom()->getOutport().x(),trackPos);
        QPointF second(edge->getTo()->getInport().x(),trackPos);
        edge->addBend(first);
        edge->addBend(second);
    }

    qreal toMove = lowestPoint + nrUsedTracks*15 + 35;
    /*for(AbstractNode* node : lower) {
        node->setY(toMove);
    }*/

    return fromTrack+nrUsedTracks;

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
