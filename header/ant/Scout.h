#ifndef ANT_SCOUT_H
#define ANT_SCOUT_H

#include "Ant.h"
#include "AntAge.h"
#include "../Config.h"

class Scout : public Ant, public AntAge {

public:
    Scout(BoardCell *currentCell) :
            Ant(Config::DEFAULT_HOURS_BEFORE_DEATH, Config::DEFAULT_FOOD_CONSUMING_TICK, currentCell),
            AntAge(Config::SCOOT_HOURS_BEFORE_ADULT) {};

};


#endif
