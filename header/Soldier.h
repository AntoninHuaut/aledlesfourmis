#ifndef ANT_SOLDIER_H
#define ANT_SOLDIER_H

#include "Ant.h"
#include "Config.h"

class Soldier : public Ant {

    int daySinceColonyVisited = 0;

public:
    Soldier() : Ant(Config::DEFAULT_DAY_BEFORE_DEATH, Config::DEFAULT_FOOD_CONSUMING_TICK) {};

};


#endif
