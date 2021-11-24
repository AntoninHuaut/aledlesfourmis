#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "Config.h"

class Worker : public Ant {

    double pheromoneAmount = 500;
    double foodCarriedAmount = 0;

    void dropFood() {};

    void visitColony() {};

public:
    Worker(BoardCell *currentCell) : Ant(Config::DEFAULT_HOURS_BEFORE_DEATH, Config::DEFAULT_FOOD_CONSUMING_TICK,
                                         currentCell) {};

};


#endif
