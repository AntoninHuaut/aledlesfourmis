#ifndef ANT_QUEEN_H
#define ANT_QUEEN_H

#include "Ant.h"
#include "Config.h"

class Queen : public Ant {

    int nbChild = 0;
    bool wasAssaulted = false;

public:
    Queen(BoardCell *currentCell) : Ant(Config::QUEEN_HOURS_BEFORE_DEATH, Config::QUEEN_FOOD_CONSUMING_TICK,
                                        currentCell) {};

    void tick() override;

};


#endif