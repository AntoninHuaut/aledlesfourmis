#ifndef ANT_ROCKCELL_H
#define ANT_ROCKCELL_H

#include "BoardCell.h"
#include "../Config.h"

class RockCell : public BoardCell {

public:
    RockCell(int posLength, int posHeight) :
            BoardCell(posLength, posHeight, Config::ROCK_MAX_ANT_ON_CELL, RockCellType) {};

};


#endif
