#ifndef ANT_BASICCELL_H
#define ANT_BASICCELL_H

#include "BoardCell.h"
#include "../ant/Ant.h"
#include "../Config.h"

class BasicCell : public BoardCell {

    double foodAmount = 0;

public:
    BasicCell(int posHeight, int posLength) :
            BoardCell(posHeight, posLength, Config::get()->getBasicCellMaxAntOnCell(), BasicCellType) {};

    void takeFood(Ant *ant);

    void setFoodAmount(double newFoodAmount) { this->foodAmount = newFoodAmount; };

    double getFoodAmount() const { return this->foodAmount; };

    int numberOfLayers() override;

    list<int> getBottomLayerTileNumbers() override;
    
};

#endif
