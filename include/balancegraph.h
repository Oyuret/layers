#ifndef BALANCEGRAPH_H
#define BALANCEGRAPH_H
#include <QList>
#include <QMap>
#include <QQueue>
#include <limits>
#include <algorithm>
#include "algorithm.h"
#include "abstract_node.h"

class Region;

class Segment {
public:
    Segment();
    virtual ~Segment(){}

    double dForce;
    int topologicNumber;
    QList<AbstractNode*> nodes;
    QList<Segment*> successors;
    QList<Segment*> predecessors;
    Region* region;
};

class Region {
public:
    Region();
    virtual ~Region() {}
    int minTopologicNumber;
    QList<Segment*> segments;
    double dForce;
    double getDforce();
};

class BalanceGraph : public Algorithm
{
public:
    BalanceGraph();
    virtual ~BalanceGraph();
    virtual void run(Graph& graph);
private:

    enum direction {UP, DOWN};

    void generateLinearSegments(Graph& graph);
    void createTrivialLinearSegment(AbstractNode* node);
    void createLinearSegment(AbstractNode* node);

    void connectLinearSegments(Graph& graph);
    void topologicSorting();
    void initialPositioning(Graph& graph);



    void newPendulum(Graph& graph);
    void newSweep(Graph& graph, direction direction);
    void newProcessRegion(Region* region, Graph& graph);

    void calculateDownForces();
    void calculateUpForces();
    void reset();

    QMap<AbstractNode*,Segment*> nodeToSegment;
    QList<Segment*> segments;
};

#endif // BALANCEGRAPH_H
