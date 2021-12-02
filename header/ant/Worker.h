#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "AgeAdult.h"
#include "../Config.h"

class Worker : public Ant, public AgeAdult {

    double pheromoneAmount = 500;
    double foodCarriedAmount = 0;

    void dropFood(); // TODO

    void visitColony(); // TODO

    void putPheromones(); // TODO

public:
    explicit Worker(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), 1, Config::get()->getDefaultFoodConsumingTick(),
                currentCell, WorkerType),
            AgeAdult(Config::get()->getWorkerHoursBeforeAdult()) {};

    bool eatFood(float amountToEat) override;
};


#endif
