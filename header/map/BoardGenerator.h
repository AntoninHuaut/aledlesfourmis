#ifndef ANT_BOARDGENERATOR_H
#define ANT_BOARDGENERATOR_H

#include <cstdlib>
#include <stdexcept>
#include <cmath>

#include "Board.h"
#include "BoardCell.h"
#include "BasicCell.h"
#include "RockCell.h"
#include "ColonyCell.h"
#include "../Config.h"

using namespace std;

class BoardGenerator {

    Board *board;

    static BoardGenerator *createBoard();

    void generateRock();

    void generateBasicCell();

public:
    explicit BoardGenerator(Board *board) {
        this->board = board;
    }

    Board *getBoard() { return board; }

    static Board *generateBoard();
};

#endif
