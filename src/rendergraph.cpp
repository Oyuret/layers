#include "include/rendergraph.h"
#include <QDebug>

RenderGraph::RenderGraph() :
    Algorithm()
{
}

void RenderGraph::run(Graph &graph)
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

    // Assign tracks and stuff
    for(int i=0; i<graph.getLayers().size() - 1; ++i) {
        assignTracks(graph.getLayers().at(i), graph.getLayers().at(i+1), graph);
    }

    graph.adjustAllEdges();

    // revert the reverted edges
    for(EdgeItem* edge : graph.getReversedEdges()) {
        edge->reverse(true);
    }

    // hide the dummy nodes
    for(const QList<AbstractNode*>& layer : graph.getLayers()) {
        for(AbstractNode* node: layer) {
            if(node->isDummy()) {
                node->hide();
            }
        }
    }



    emit setStatusMsg("Rendering graph...Done!");
}

void RenderGraph::assignTracks(const QList<AbstractNode *>& upper, const QList<AbstractNode*>& lower, Graph& graph)
{
    // Add all edges to the timeline
    QList<QPair<qreal,EdgeItem*>> timeLine;
    for(AbstractNode* from : upper) {
        for(AbstractNode* to : from->getSuccessors()) {
            QList<EdgeItem*> edges = graph.findEdge(from,to);

            for(EdgeItem* edge : edges) {

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

        // No tracks taken
        /*if(takenTracks.isEmpty()) {
            takenTracks.insert(edge.second,0);
            assignedTracks.insert(edge.second,0);
            nrUsedTracks = std::max(nrUsedTracks,1);
            continue;
        }*/

        // tracks currently taken
        /*QList<int> takenTrackNumbers = takenTracks.values();

        for(int i=0; i<nrUsedTracks+10 ; i++) {
            if(takenTrackNumbers.contains(i)) {
                continue;
            } else {
                takenTracks.insert(edge.second,i);
                assignedTracks.insert(edge.second,i);
                nrUsedTracks = std::max(nrUsedTracks,i+1);
                break;
            }
        }*/
    }


    // Add bends
    qreal lowestPoint = upper.first()->y() + upper.first()->boundingRect().height();
    for(AbstractNode* node : upper) {
        lowestPoint = std::max(lowestPoint, node->y() + node->boundingRect().height());
    }
    lowestPoint = lowestPoint + 35;

    for(EdgeItem* edge : assignedTracks.keys()) {
        qreal trackPos = lowestPoint + (15*assignedTracks.value(edge));
        QPointF first(edge->getFrom()->getOutport().x(),trackPos);
        QPointF second(edge->getTo()->getInport().x(),trackPos);
        edge->addBend(first);
        edge->addBend(second);
    }

    qreal toMove = lowestPoint + nrUsedTracks*15 + 35;
    for(AbstractNode* node : lower) {
        node->setY(toMove);
    }

}
