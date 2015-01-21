#include "include/abstract_edge.h"

AbstractEdge::AbstractEdge() :
    reversed(false)
{
}


AbstractEdge::AbstractEdge(AbstractNode *from, AbstractNode *to) :
    from(from), to(to), reversed(false)
{

}

bool AbstractEdge::isReversed() const
{
    return reversed;
}

void AbstractEdge::swapReversed()
{
    reversed = !reversed;
}
