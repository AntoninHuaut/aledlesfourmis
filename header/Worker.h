#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "Config.h"

class Worker : public Ant {

    double pheromoneAmount = 500;
    double foodCarriedAmount = 0;

    void dropFood();

    void visitColony();

public:
    Worker() : Ant(Config::DEFAULT_DAY_BEFORE_DEATH, Config::DEFAULT_FOOD_CONSUMING_TICK) {};

};


#endif
