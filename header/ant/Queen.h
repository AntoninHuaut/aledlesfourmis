#ifndef ANT_QUEEN_H
#define ANT_QUEEN_H

#include "Ant.h"
#include "../Config.h"

class Queen : public Ant {

    int nbChild = 0;
    bool wasAssaulted = false;

public:
    explicit Queen(BoardCell *currentCell) :
            Ant(Config::get()->getQueenHoursBeforeDeath(), Config::get()->getQueenFoodConsumingTick(),
                currentCell) {};

    void tick() override;

};


#endif