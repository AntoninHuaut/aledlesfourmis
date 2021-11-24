#ifndef ANT_SOLDIER_H
#define ANT_SOLDIER_H

#include "Ant.h"
#include "Config.h"

class Soldier : public Ant {

    int hoursSinceColonyVisited = 0;

public:
    Soldier(BoardCell *currentCell) : Ant(Config::DEFAULT_HOURS_BEFORE_DEATH, Config::DEFAULT_FOOD_CONSUMING_TICK,
                                          currentCell) {};

};


#endif
