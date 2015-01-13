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

    generateLinearSegments(graph);
    connectLinearSegments(graph);
    topologicSorting();
    initialPositioning(graph);
    graph.adjustAllEdges();


    // Start the pendulum algorithm

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

    for(Segment* segment : segments) {
        if(segment->predecessors.isEmpty()) {
            queue.enqueue(segment);
            topologicSorted.append(segment);
        }
    }

    while(!queue.isEmpty()) {
        Segment* segment = queue.dequeue();

        for(Segment* succ : segment->successors) {
            succ->predecessors.removeOne(segment);

            if(succ->predecessors.isEmpty()) {
                queue.enqueue(succ);
                topologicSorted.append(succ);
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

        for (AbstractNode* n : s->nodes) {
            minPos[n->getLayer()] = max + n->boundingRect().width() + 50;
            n->setX(max);
        }
    }
}

void BalanceGraph::generateDownRegions()
{

}

void BalanceGraph::generateUpRegions()
{

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
