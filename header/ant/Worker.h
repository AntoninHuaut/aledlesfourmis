#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "AntAge.h"
#include "../Config.h"

class Worker : public Ant, public AntAge {

    double pheromoneAmount = 500;
    double foodCarriedAmount = 0;

    void dropFood() {};

    void visitColony() {};

public:

    explicit Worker(BoardCell *currentCell) :
            Ant(Config::DEFAULT_HOURS_BEFORE_DEATH, Config::DEFAULT_FOOD_CONSUMING_TICK, currentCell),
            AntAge(Config::WORKER_HOURS_BEFORE_ADULT) {};

};


#endif
