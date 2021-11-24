#ifndef ANT_BOARDGENERATOR_H
#define ANT_BOARDGENERATOR_H

#include <cstdlib>
#include <stdexcept>

#include "Board.h"

using namespace std;

#define BOARD_LENGTH 211
#define BOARD_HEIGHT 201
#define ROCK_PERCENT 0.03

class BoardGenerator {

    Board *board;

    static BoardGenerator *createBoard();

    void generateRock();

public:
    explicit BoardGenerator(Board *board) {
        this->board = board;
    }

    static Board *generateBoard();
};

#endif
