#ifndef ANT_COLONYCELL_H
#define ANT_COLONYCELL_H

#include "BoardCell.h"
#include "../Config.h"

class ColonyCell : public BoardCell {

public:
    ColonyCell(int posLength, int posHeight) : BoardCell(posLength, posHeight, Config::COLONY_MAX_ANT_ON_CELL) {};

};

#endif
