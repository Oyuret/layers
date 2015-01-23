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
    int getPositionInLayer() const;
    void setPositionInLayer(int position);
    double getDownsweepWeight() const;
    double getUpsweepWeight() const;

    const AbstractNode* getFirstSucc() const;

    QList<AbstractNode*>& getIbeds();
    QList<AbstractNode*>& getObeds();

    virtual bool isDummy() const;
    virtual bool isIbed() const;
    virtual bool isObed() const;

    virtual ~AbstractNode(){}

private:
    int layer;
    int positionInLayer;
    QList<AbstractNode*> successors;
    QList<AbstractNode*> predecessors;
    QList<AbstractNode*> ibeds;
    QList<AbstractNode*> obeds;
};

#endif // ABSTRACTNODE_H
