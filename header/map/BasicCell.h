#ifndef ANT_BASICCELL_H
#define ANT_BASICCELL_H

#include "BoardCell.h"
#include "../ant/Ant.h"

class BasicCell : public BoardCell {

    double foodAmount = 0;

public:
    BasicCell(int posLength, int posHeight, int maxAntOnCell) : BoardCell(posLength, posHeight, maxAntOnCell) {};

    void takeFood(Ant *ant);

    void setFoodAmount(double newFoodAmount) { this->foodAmount = newFoodAmount; };

    double getFoodAmount() { return this->foodAmount; };
};

#endif
