#ifndef ANT_GAME_H
#define ANT_GAME_H

#include "../map/Board.h"

class Game {

    Board *board;

    void tickAnts();

    void tickQueen();
    
    bool checkAndRemoveDeadAnt(Ant *ant);

public:

    explicit Game(Board *board) {
        this->board = board;
    }

    void tickGame();
};


#endif