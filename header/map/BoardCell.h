#ifndef ANT_BOARDCELL_H
#define ANT_BOARDCELL_H

#include <list>
#include "../ant/Ant.h"

using namespace std;

class BoardCell {

    int posLength;
    int posHeight;

    double pheromoneAmount = 0;
    bool visited = false;
    int maxAntOnCell = 0;
    list<Ant *> *antOnCell{};

    void pheromoneSpreading() {};

public:
    explicit BoardCell(int posLength, int posHeight, int maxAntOnCell) {
        this->maxAntOnCell = maxAntOnCell;
        this->posLength = posLength;
        this->posHeight = posHeight;
    };

    virtual void tick() {};

    int getMaxAntOnCell() const { return maxAntOnCell; };


};

#endif
