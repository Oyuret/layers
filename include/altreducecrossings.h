#ifndef ALTREDUCECROSSINGS_H
#define ALTREDUCECROSSINGS_H
#include "algorithm.h"

class AltReduceCrossings : public Algorithm
{
public:
    AltReduceCrossings();
    virtual ~AltReduceCrossings(){}

    virtual void run(Graph& graph);

private:
    void downsweep(Graph& graph);
    void upsweep(Graph& graph);
    int calculateDownsweepWeight();
    int calculateUpsweepWeight();
    void updatePositionings(QList<AbstractNode *> &layer);
};

#endif // ALTREDUCECROSSINGS_H
