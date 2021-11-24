#ifndef ANT_QUEEN_H
#define ANT_QUEEN_H

#include "Ant.h"
#include "Config.h"

class Queen : public Ant {

    int nbChild = 0;
    bool wasAssaulted = false;

public:
    Queen() : Ant(Config::QUEEN_DAY_BEFORE_DEATH, Config::QUEEN_FOOD_CONSUMING_TICK) {};

    void tick() override;

};


#endif