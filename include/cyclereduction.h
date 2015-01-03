#ifndef CYCLEREDUCTION_H
#define CYCLEREDUCTION_H
#include <QSet>
#include <QStack>
#include "algorithm.h"
#include "abstract_node.h"
#include "edgeitem.h"
#include "graph.h"

class CycleReduction : public Algorithm
{
public:
    CycleReduction();
    virtual void run(Graph& graph);
    virtual ~CycleReduction(){}
private:
    void DFS(AbstractNode* node, Graph &graph);
    QSet<AbstractNode*> visited;
    QSet<AbstractNode*> active;
};

#endif // CYCLEREDUCTION_H
