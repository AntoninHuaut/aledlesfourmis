#ifndef ANT_SOLDIER_H
#define ANT_SOLDIER_H

#include "Ant.h"
#include "../Config.h"

class Soldier : public Ant {

    int hoursSinceColonyVisited = 0;

public:
    explicit Soldier(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultFoodConsumingTick(),
                currentCell, SoldierType) {};

};


#endif
