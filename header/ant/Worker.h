#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "Age.h"
#include "../Config.h"

class Worker : public Ant, public Age {

    double pheromoneAmount = 500;
    double foodCarriedAmount = 0;

    void dropFood() {};

    void visitColony() {};

public:
    explicit Worker(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultFoodConsumingTick(),
                currentCell, WorkerType),
            Age(Config::get()->getWorkerHoursBeforeAdult()) {};

};


#endif
