#include "include/cfg.h"


Block::Block()
{

}

Block::Block(QString name) :
    name(name)
{

}

void Block::addPredecessor(QString predecessor)
{
    predecessors.push_back(predecessor);
}

void Block::addSuccessor(QString successor)
{
    successors.push_back(successor);
}

void Block::setName(QString name)
{
    this->name = name;
}

const list<QString> &Block::getPredecessors() const
{
    return predecessors;
}

const list<QString> &Block::getSuccessors() const
{
    return successors;
}

const QString Block::getName() const
{
    return name;
}

CFG::CFG()
{
}

void CFG::addBlock(Block block)
{
    blocks.push_back(block);
}

void CFG::addStartBlock(Block block)
{
    start = block;
}

const list<Block> &CFG::getBlocks() const
{
    return blocks;
}

const Block CFG::getStart() const
{
    return start;
}
