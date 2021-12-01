#ifndef ANT_ROCKCELL_H
#define ANT_ROCKCELL_H

#include "BoardCell.h"
#include "../Config.h"

using namespace std;

class RockCell : public BoardCell {

public:
    RockCell(int posLength, int posHeight) :
            BoardCell(posLength, posHeight, Config::get()->getRockMaxAntOnCell(), RockCellType) {};

};


#endif
