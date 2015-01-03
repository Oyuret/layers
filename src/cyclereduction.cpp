#include "include/cyclereduction.h"

CycleReduction::CycleReduction()
{
}

void CycleReduction::run(Graph &graph)
{

    emit setStatusMsg("Reducing crossings...");

    //reset
    visited.clear();
    active.clear();
    graph.resetReversed();

    AbstractNode* start = graph.getStart();

    // Start by reversing all incoming edges to start
    QList<AbstractNode*> preds = start->getPredecessors();
    for(AbstractNode* predecessor : preds) {
        graph.reverseEdge(predecessor,start);
    }

    // Start reversing edges
    DFS(start, graph);

    emit setStatusMsg("Reducing crossings... Done!");

}

void CycleReduction::DFS(AbstractNode *node, Graph& graph)
{
    QStack<AbstractNode*> stack;
    stack.push(node);

    while(!stack.isEmpty()) {
        AbstractNode* node = stack.pop();

        if(visited.contains(node)) {
            active.remove(node);
            continue;
        }

        stack.push(node);
        visited.insert(node);
        active.insert(node);

        QList<AbstractNode*> successors = node->getSuccessors();
        for(AbstractNode* succ : successors) {
            if(active.contains(succ)) {
                graph.reverseEdge(node,succ);
            } else if(!visited.contains(succ)) {
                stack.push(succ);
            }
        }
    }
}
