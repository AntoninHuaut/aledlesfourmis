#ifndef ANT_BASICCELL_H
#define ANT_BASICCELL_H

#include "BoardCell.h"
#include "../ant/Ant.h"
#include "../Config.h"

class BasicCell : public BoardCell {

    double foodAmount = 0;

public:
    BasicCell(int posLength, int posHeight) :
            BoardCell(posLength, posHeight, Config::BASIC_CELL_MAX_ANT_ON_CELL, BasicCellType) {};

    void takeFood(Ant *ant);

    void setFoodAmount(double newFoodAmount) { this->foodAmount = newFoodAmount; };

    double getFoodAmount() const { return this->foodAmount; };
};

#endif
