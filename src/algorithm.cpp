#include "include/algorithm.h"

Algorithm::Algorithm()
{
}

void Algorithm::run(Graph& graph)
{
    emit setStatusMsg("En Test");
}

void Algorithm::run(Graph &graph, QGraphicsScene *scene)
{
    Q_UNUSED(graph);
    Q_UNUSED(scene);
    emit setStatusMsg("Recombobulating splines");
}
