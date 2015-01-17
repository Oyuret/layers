#ifndef BALANCEGRAPH_H
#define BALANCEGRAPH_H
#include <QList>
#include <QMap>
#include <QQueue>
#include <limits>
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

    void pendulum(Graph& graph);
    double calculateZForce(Graph& graph);
    void sweep(Graph& graph, direction direction);
    void calculateDownForces();
    void calculateUpForces();
    void generateDownRegions();
    void generateUpRegions();
    void reset();

    QMap<AbstractNode*,Segment*> nodeToSegment;
    QList<Segment*> segments;
};

#endif // BALANCEGRAPH_H
