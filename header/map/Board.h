#ifndef ANT_BOARD_H
#define ANT_BOARD_H

#include "BoardCell.h"
//#include "ColonyCell.h"

using namespace std;

class Board {

    BoardCell ***cells;
//    list<ColonyCell*> coloniesCells;

public:
    explicit Board(BoardCell ***cells/*, list<ColonyCell*> coloniesCells*/) {
        this->cells = cells;
//        this->coloniesCells = coloniesCells;
    };

    BoardCell ***getCells() { return cells; }

    list<BoardCell *> getNearbyCells(BoardCell *cell);
};

#endif