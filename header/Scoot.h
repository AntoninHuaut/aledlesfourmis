#ifndef ANT_SCOOT_H
#define ANT_SCOOT_H

#include "Ant.h"
#include "Config.h"

class Scoot : public Ant {

public:
    Scoot() : Ant(Config::DEFAULT_DAY_BEFORE_DEATH, Config::DEFAULT_FOOD_CONSUMING_TICK) {};

};


#endif
