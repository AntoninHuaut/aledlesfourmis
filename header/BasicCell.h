#ifndef ANT_BASICCELL_H
#define ANT_BASICCELL_H

#include "BoardCell.h"
#include "Ant.h"

class BasicCell : public BoardCell {

    double foodAmount = 0;

public:
    BasicCell(int maxAntOnCell) : BoardCell(maxAntOnCell) {};

    void takeFood(Ant *ant);
};

#endif
