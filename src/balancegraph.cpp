#include "include/balancegraph.h"
#include <QDebug>

BalanceGraph::BalanceGraph() :
    Algorithm()
{
}

BalanceGraph::~BalanceGraph()
{
    for(Segment* segment : segments) {
        delete segment;
    }
}

void BalanceGraph::run(Graph &graph)
{
    reset();

    emit setStatusMsg("Balancing graph...");

    // Generate a starting layout
    generateLinearSegments(graph);
    connectLinearSegments(graph);
    topologicSorting();
    initialPositioning(graph);
    graph.adjustAllEdges();

    // Start the pendulum algorithm
    newPendulum(graph);
    graph.adjustAllEdges();

    emit setStatusMsg("Balancing graph... Done!");
}

void BalanceGraph::generateLinearSegments(Graph &graph)
{
    for(QList<AbstractNode*>& layer : graph.getLayers()) {
        for(AbstractNode* node : layer) {

            // Already assigned
            if(nodeToSegment.contains(node)) {
                continue;
            }

            // If we have only one successor we are the start of a chain
            if(node->getSuccessors().size() == 1) {
                createLinearSegment(node);
                continue;
            }

            // Every other case is a trivial linear segment
            createTrivialLinearSegment(node);

        }
    }
}

void BalanceGraph::createTrivialLinearSegment(AbstractNode *node)
{
    // Create a segment
    Segment* segment = new Segment();
    segments.push_back(segment);
    segment->nodes.append(node);
    nodeToSegment.insert(node,segment);
}

void BalanceGraph::createLinearSegment(AbstractNode *node)
{
    // Create a segment
    Segment* segment = new Segment();
    segments.push_back(segment);

    // Add the head of the chain
    segment->nodes.push_back(node);
    nodeToSegment.insert(node,segment);

    AbstractNode* currentNode = node->getSuccessors().first();

    // We are still within in the chain
    while(currentNode->getPredecessors().size() == 1 && currentNode->getSuccessors().size() == 1) {
        segment->nodes.push_back(currentNode);
        nodeToSegment.insert(currentNode,segment);
        currentNode = currentNode->getSuccessors().first();
    }

    // We are at the end of the chain now

    // If we have many predecessors, let it be
    if(currentNode->getPredecessors().size() > 1) {
        return;
    }

    // if we have no successors, end of chain, add and return
    if(currentNode->getSuccessors().isEmpty()) {
        segment->nodes.push_back(currentNode);
        nodeToSegment.insert(currentNode,segment);
    }
}

void BalanceGraph::connectLinearSegments(Graph &graph)
{
    for(QList<AbstractNode*> layer : graph.getLayers()) {
        AbstractNode* prev = nullptr;

        for(AbstractNode* node : layer) {
            if(prev != nullptr) {
                Segment* left = nodeToSegment.value(prev);
                Segment* right = nodeToSegment.value(node);

                if(left != right) {
                    left->successors.append(right);
                    right->predecessors.append(left);
                }
            }
            prev = node;
        }
    }
}

void BalanceGraph::topologicSorting()
{
    QQueue<Segment*> queue;
    QList<Segment*> topologicSorted;

    int topologicIndex = 0;
    for(Segment* segment : segments) {
        if(segment->predecessors.isEmpty()) {
            segment->topologicNumber = topologicIndex;
            queue.enqueue(segment);
            topologicSorted.append(segment);
            topologicIndex++;
        }
    }

    while(!queue.isEmpty()) {
        Segment* segment = queue.dequeue();

        for(Segment* succ : segment->successors) {
            succ->predecessors.removeOne(segment);

            if(succ->predecessors.isEmpty()) {
                succ->topologicNumber = topologicIndex;
                queue.enqueue(succ);
                topologicSorted.append(succ);
                topologicIndex++;
            }
        }
    }

    segments = topologicSorted;
}

void BalanceGraph::initialPositioning(Graph& graph)
{
    int minPos[graph.getLayers().size()];

    // Set all minPos to 0
    for(int i=0; i< graph.getLayers().size(); ++i) {
        minPos[i] = 0;
    }

    for (Segment* s : segments) {
        int max = 0;
        for (AbstractNode* n : s->nodes) {
            int x = minPos[n->getLayer()];
            if (x > max) {
                max = x;
            }
        }

        qreal maxWidth = s->nodes.first()->boundingRect().width();
        for(AbstractNode* n : s->nodes) {
            maxWidth = std::max(n->boundingRect().width(),maxWidth);
        }


        for (AbstractNode* n : s->nodes) {
            qreal offset = (maxWidth - n->boundingRect().width())/2;
            n->setX(max + offset);

            minPos[n->getLayer()] = n->x() + n->boundingRect().width() + offset + 25;
        }
    }
}

void BalanceGraph::newPendulum(Graph &graph)
{
    int i = 0;
    while(i < 600) {
        newSweep(graph,DOWN);
        newSweep(graph,UP);
        i++;
    }
    newSweep(graph,DOWN);
    newSweep(graph,DOWN);
    newSweep(graph,DOWN);
}

void BalanceGraph::newSweep(Graph &graph, BalanceGraph::direction direction)
{
    if(direction == DOWN) {
        calculateDownForces();
    } else {
        calculateUpForces();
    }

    // Generate trivial regions
    QList<Region*> regions;
    for(Segment* segment : segments) {
        Region* region = new Region();
        segment->region = region;
        region->minTopologicNumber = segment->topologicNumber;
        region->segments.append(segment);
        regions.append(region);
    }

    // Combine regions
    bool regionsChanged = true;
    while(regionsChanged) {
        regionsChanged = false;

        // Combine
        for(Segment* segment : segments) {
            for(AbstractNode* left : segment->nodes) {
                int layer = left->getLayer();
                int positionOfLeft = left->getPositionInLayer();

                // if we are last in the layer
                if(positionOfLeft == graph.getLayers().at(layer).size()-1) {
                    continue;
                }

                AbstractNode* right = graph.getLayers().at(layer).at(positionOfLeft+1);

                Region* leftRegion = nodeToSegment.value(left)->region;
                Region* rightRegion = nodeToSegment.value(right)->region;

                // if we are the same region just continue
                if(leftRegion == rightRegion) {
                    continue;
                }

                // we are touching another node
                if(right->x() <=  (left->x() + 25 + left->boundingRect().width())) {

                    // if we are about to walk into each other
                    if(leftRegion->getDforce() >= rightRegion->getDforce()) {
                        regionsChanged = true;

                        for(Segment* s : rightRegion->segments) {
                            leftRegion->segments.append(s);
                            s->region = leftRegion;
                            leftRegion->minTopologicNumber = std::min(leftRegion->minTopologicNumber,s->topologicNumber);
                        }
                        delete rightRegion;
                        regions.removeAll(rightRegion);
                    }

                }

            }
        } // Combining regions

    } // While regions not changed

    /*
    for(Region* r : regions) {
        qDebug() << "Region:";
        for(Segment* s : r->segments) {
            qDebug() << s->nodes.first()->getName();
        }
    }
    */

    // Order by minTopologicalNumber
    std::sort(regions.begin(),regions.end(),[](const Region* const r1, const Region* const r2){return r1->minTopologicNumber < r2->minTopologicNumber;});


    // Process each region
    for(Region* r : regions) {
        newProcessRegion(r,graph);
    }




    // Done. Delete regions
    for(Region* r : regions) {
        delete r;
    }

}

void BalanceGraph::newProcessRegion(Region *region, Graph &graph)
{
    // if we do not need to move the region
    if(region->getDforce() == 0) {
        return;
    }

    double minMovement = region->getDforce();
    if(minMovement < 0) {
        minMovement = (-1)*minMovement;
    }

    for(Segment* s : region->segments) {
        for(AbstractNode* node : s->nodes) {
            int layer = node->getLayer();
            int positionInLayer = node->getPositionInLayer();

            // attempting to move to the left
            if(region->getDforce() < 0) {

                // If we are the leftmost node
                if(positionInLayer == 0) {
                    continue;
                }

                AbstractNode* leftNode = graph.getLayers().at(layer).at(positionInLayer-1);

                // if leftNode is in the same region
                if(nodeToSegment.value(leftNode)->region == s->region) {
                    continue;
                }

                double availableMovement = node->x() - (leftNode->x() + leftNode->boundingRect().width() + 25);

                if(availableMovement < minMovement) {
                    minMovement = availableMovement;
                }
            }

            // Attempting to move to the right
            if(region->getDforce() > 0) {

                // if we are the rightmost in layer
                if(positionInLayer == graph.getLayers().at(layer).size()-1) {
                    continue;
                }

                AbstractNode* rightNode = graph.getLayers().at(layer).at(positionInLayer+1);

                // if rightNode is in the same region
                if(nodeToSegment.value(rightNode)->region == s->region) {
                    continue;
                }

                double availableMovement = rightNode->x() - (node->x() + node->boundingRect().width() + 25);

                if(availableMovement < minMovement) {
                    minMovement = availableMovement;
                }

            }
        }
    } // Calculate the maximal movement

    // move the whole region
    for(Segment* s : region->segments) {
        for(AbstractNode* n : s->nodes) {

            // movement to the left
            if(region->getDforce() < 0) {
                n->moveBy(-minMovement,0);
            } else {
                n->moveBy(minMovement,0);
            }
        }
    }

}

void BalanceGraph::calculateDownForces()
{
    for(Segment* segment : segments) {
        AbstractNode* head = segment->nodes.first();

        if (head->getPredecessors().isEmpty()) {
            segment->dForce = 0;
        } else {
            qreal sum = 0;
            for(AbstractNode* pred : head->getPredecessors()) {
                sum += pred->getOutport().x() - head->getInport().x();
            }
            segment->dForce = (double) (sum / head->getPredecessors().size());
        }
    }
}

void BalanceGraph::calculateUpForces()
{
    for(Segment* segment : segments) {
        AbstractNode* tail = segment->nodes.last();

        if (tail->getSuccessors().isEmpty()) {
            segment->dForce = 0;
        } else {
            qreal sum = 0;
            for(AbstractNode* succ : tail->getSuccessors()) {
                sum += succ->getInport().x() -  tail->getOutport().x();
            }
            segment->dForce = (double) (sum / tail->getSuccessors().size());
        }
    }

}

void BalanceGraph::reset()
{
    for(Segment* segment : segments) {
        delete segment;
    }
    segments.clear();
    nodeToSegment.clear();
}


Segment::Segment() :
    region(nullptr)
{
}


Region::Region()
{

}

double Region::getDforce()
{
    double sum = 0;

    for(Segment* s : segments) {
        sum += s->dForce;
    }

    return sum / segments.size();
}
