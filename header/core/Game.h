#ifndef ANT_GAME_H
#define ANT_GAME_H

#include "../map/Board.h"

class Game {

    Board *board{};

public:
    explicit Game(Board *board) {
        this->board = board;
    }

    void tickGame();

    void tickAnts();

    void tickQueen();
};


#endif