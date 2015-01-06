#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H
#include <QList>
#include "blockitem.h"

using namespace std;

class AbstractNode : public BlockItem
{
public:
    AbstractNode();
    AbstractNode(QString name, int width, int height);
    void addSuccessor(AbstractNode* successor);
    void addPredecessor(AbstractNode* predecessor);
    QList<AbstractNode*>& getSuccessors();
    QList<AbstractNode*>& getPredecessors();
    void removePredecessor(AbstractNode* node);
    void removeSuccessor(AbstractNode* node);
    void setLayer(int layer);
    int getLayer() const;
    virtual ~AbstractNode(){}

private:
    int layer;
    QList<AbstractNode*> successors;
    QList<AbstractNode*> predecessors;
};

#endif // ABSTRACTNODE_H
