#ifndef ANT_BOARDCELL_H
#define ANT_BOARDCELL_H

#include <list>
#include "Ant.h"

using namespace std;

class BoardCell {
    double pheromoneAmount = 0;
    bool visited = false;
    int maxAntOnCell = 0;
    list<Ant *> *antOnCell;

    void pheromoneSpreading() {};

public:
    explicit BoardCell(int maxAntOnCell) {
        this->maxAntOnCell = maxAntOnCell;
    };

    virtual void tick() {};

    int getMaxAntOnCell() const { return maxAntOnCell; };


};

#endif
