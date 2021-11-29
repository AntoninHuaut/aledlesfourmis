#ifndef ANT_SCOUT_H
#define ANT_SCOUT_H

#include "Ant.h"
#include "Age.h"
#include "../Config.h"

class Scout : public Ant, public Age {

public:
    explicit Scout(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultFoodConsumingTick(),
                currentCell, ScoutType),
            Age(Config::get()->getScootHoursBeforeAdult()) {};

};


#endif
