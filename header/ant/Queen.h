#ifndef ANT_QUEEN_H
#define ANT_QUEEN_H

#include "Ant.h"
#include "../Config.h"

class Queen : public Ant {

    int nbChild = 0;
    bool wasAssaulted = false;

public:
    explicit Queen(BoardCell *currentCell) :
            Ant(Config::get()->getQueenHoursBeforeDeath(), 1, Config::get()->getQueenFoodConsumingTick(),
                currentCell, QueenType) {};

    void tick(Board *board) override;
};


#endif