#ifndef CFG_H
#define CFG_H
#include <list>
#include <QString>

using namespace std;

class Block
{
public:
    Block();
    Block(QString name);
    void addPredecessor(QString predecessor);
    void addSuccessor(QString successor);
    void setName(QString name);
    const list<QString>& getPredecessors() const;
    const list<QString>& getSuccessors() const;
    const QString getName() const;
    virtual ~Block(){}
private:
    list<QString> predecessors;
    list<QString> successors;
    QString name;
};

class CFG
{
public:
    CFG();
    void addBlock(Block block);
    void addStartBlock(Block block);
    const list<Block>& getBlocks() const;
    const Block getStart() const;
    virtual ~CFG(){}
private:
    list<Block> blocks;
    Block start;
};

#endif // CFG_H
