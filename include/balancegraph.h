#ifndef BALANCEGRAPH_H
#define BALANCEGRAPH_H
#include <QList>
#include <QMap>
#include <QQueue>
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
    void generateLinearSegments(Graph& graph);
    void createTrivialLinearSegment(AbstractNode* node);
    void createLinearSegment(AbstractNode* node);

    void connectLinearSegments(Graph& graph);
    void topologicSorting();
    void initialPositioning(Graph& graph);

    void generateDownRegions();
    void generateUpRegions();
    void reset();

    QMap<AbstractNode*,Segment*> nodeToSegment;
    QList<Segment*> segments;
};

#endif // BALANCEGRAPH_H
