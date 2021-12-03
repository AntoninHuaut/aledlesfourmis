#ifndef ANT_BASICCELL_H
#define ANT_BASICCELL_H

#include "BoardCell.h"
#include "../ant/Ant.h"
#include "../Config.h"

class BasicCell : public BoardCell {

    float foodAmount = 0;

public:
    BasicCell(Board *board, int height, int length) :
            BoardCell(board, height, length, Config::get()->getBasicCellMaxAntOnCell(), BasicCellType) {};
    
    void setFoodAmount(float newFoodAmount) { this->foodAmount = newFoodAmount; };

    float getFoodAmount() const { return this->foodAmount; };

    int numberOfLayers() override;

    list<int> getLayersTileNumbers() override;

};

#endif
