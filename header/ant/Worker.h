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
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultFoodConsumingTick(), currentCell),
            AntAge(Config::get()->getWorkerHoursBeforeAdult()) {};

};


#endif
