#include "include/insertdummynodes.h"

InsertDummyNodes::InsertDummyNodes()
{
}

void InsertDummyNodes::run(Graph& graph, QGraphicsScene *scene)
{
    emit setStatusMsg("Inserting dummy nodes...");

    QList<EdgeItem*> edges = graph.getEdges();
    QList<EdgeItem*> reversedEdges = graph.getReversedEdges();

    addDummies(graph.getLayers(),graph,scene,edges);
    addReversedDummies(graph.getLayers(),graph,scene,reversedEdges);

    emit setStatusMsg("Inserting dummy nodes... Done!");
}

void InsertDummyNodes::addDummies(QList<QList<AbstractNode *> > &layers, Graph &graph, QGraphicsScene* scene,QList<EdgeItem *> edges)
{
    int dummyCount =0;
    for(EdgeItem* edge : edges) {
        AbstractNode* u = edge->getFrom();
        AbstractNode* v = edge->getTo();

        int i = u->getLayer()+1;
        int j = v->getLayer();
        AbstractNode* last = u;

        while(i != j) {

            // crate new dummy node
            //Node* dummy = new Node(QString::number(dummyCount).append("D"),25,25);
            DummyNode* dummy = new DummyNode();
            dummyCount++;
            dummy->setLayer(i);
            dummy->setX(0);
            dummy->setY(0);
            scene->addItem(dummy);
            graph.addNode(dummy);

            // Add dummy node to layer
            layers[i].prepend(dummy);

            // remove connection between last and v
            scene->removeItem(graph.getEdge(last,v));
            graph.removeEdge(last,v);

            // add connection between last and dummy
            EdgeItem* edgeLasttoDummy = new EdgeItem(last,dummy,false);
            graph.addEdge(last,dummy,edgeLasttoDummy);
            scene->addItem(edgeLasttoDummy);


            // add connection between dummy and v
            EdgeItem* edgeDummytoV = new EdgeItem(dummy,v,true);
            graph.addEdge(dummy,v,edgeDummytoV);
            scene->addItem(edgeDummytoV);

            last = dummy;

            i++;

        }
    }
}

void InsertDummyNodes::addReversedDummies(QList<QList<AbstractNode *> > &layers, Graph &graph, QGraphicsScene *scene, QList<EdgeItem *> edges)
{
    int dummyCount = 0;
    for(EdgeItem* edge : edges) {
        AbstractNode* u = edge->getFrom();
        AbstractNode* v = edge->getTo();

        int i = u->getLayer()+1;
        int j = v->getLayer();
        AbstractNode* last = u;

        while(i != j) {

            // crate new dummy node
            //Node* dummy = new Node(QString::number(dummyCount).append("R"),25,25);
            DummyNode* dummy = new DummyNode();
            dummyCount++;
            dummy->setLayer(i);
            dummy->setX(0);
            dummy->setY(0);
            scene->addItem(dummy);
            graph.addNode(dummy);

            // Add dummy node to layer
            layers[i].prepend(dummy);

            // remove connection between last and v
            scene->removeItem(graph.getReversedEdge(last,v));
            graph.removeReversedEdge(last,v);

            // add connection between last and dummy
            EdgeItem* edgeLasttoDummy = new EdgeItem(last,dummy,false);
            graph.addReversedEdge(last,dummy,edgeLasttoDummy);
            scene->addItem(edgeLasttoDummy);


            // add connection between dummy and v
            EdgeItem* edgeDummytoV = new EdgeItem(dummy,v,true);
            graph.addReversedEdge(dummy,v,edgeDummytoV);
            scene->addItem(edgeDummytoV);

            last = dummy;

            i++;

        }
    }
}
