#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "AgeAdult.h"
#include "../Config.h"

class Worker : public Ant, public AgeAdult {

    double pheromoneAmount = 500;
    float foodCarriedAmount = 0;

    void dropFood();

    void pickFood();

    void visitColony();

    void putPheromones();

public:

    explicit Worker(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), 1, Config::get()->getDefaultFoodConsumingTick(),
                currentCell, WorkerType),
            AgeAdult(Config::get()->getWorkerHoursBeforeAdult()) {};

    bool eatFood(float amountToEat) override;

    void tickMove(Board *board) override;

};


#endif
