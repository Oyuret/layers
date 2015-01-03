#include "include/abstract_edge.h"

AbstractEdge::AbstractEdge()
{
}


AbstractEdge::AbstractEdge(AbstractNode *from, AbstractNode *to) :
    from(from), to(to)
{

}
