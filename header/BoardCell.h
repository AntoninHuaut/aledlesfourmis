#ifndef ANT_BOARDCELL_H
#define ANT_BOARDCELL_H

#include <list>
#include "Ant.h"

class BoardCell
{
    double pheromoneAmount = 0;
    bool visited = false;
    int maxAntOnCell = 0;
    std::list<Ant*> antOnCell;

    void pheromoneSpreading() {};

public:
    BoardCell(int maxAnt){
        maxAntOnCell = maxAnt;
    };
    virtual void tick() {};

    int getMaxAntOnCell() { return maxAntOnCell; };


};

#endif
