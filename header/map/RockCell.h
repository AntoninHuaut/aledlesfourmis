#ifndef ANT_ROCKCELL_H
#define ANT_ROCKCELL_H

#include "BoardCell.h"
#include "../Config.h"

using namespace std;

class RockCell : public BoardCell {

public:
    RockCell(int posHeight, int posLength) :
            BoardCell(posHeight, posLength, Config::get()->getRockMaxAntOnCell(), RockCellType) {};

};


#endif
