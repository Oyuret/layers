#ifndef ASSIGNLAYERS_H
#define ASSIGNLAYERS_H
#include <QLinkedList>
#include <QSet>
#include "algorithm.h"
#include "graph.h"

using namespace std;

class AssignLayers : public Algorithm
{
public:
    AssignLayers();
    virtual void run(Graph& graph);
    virtual ~AssignLayers() {}
private:

};

#endif // ASSIGNLAYERS_H
