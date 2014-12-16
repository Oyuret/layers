#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include "abstract_node.h"

using namespace std;

class Graph
{
public:
    Graph();
    virtual ~Graph(){}

private:
    list<AbstractNode*> nodes;
    list<list<AbstractNode*>> layers;

};

#endif // GRAPH_H
