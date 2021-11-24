#ifndef ANT_BOARD_H
#define ANT_BOARD_H

#include "BoardCell.h"
//#include "ColonyCell.h"

using namespace std;
w
class Board {

    list<BoardCell *> cells;
//    list<ColonyCell*> coloniesCells;

public:
    Board(list<BoardCell *> cells/*, list<ColonyCell*> coloniesCells*/) {
        this->cells = cells;
//        this->coloniesCells = coloniesCells;
    };
};

#endif