#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "AgeAdult.h"
#include "../Config.h"

class Worker : public Ant, public AgeAdult {

    float pheromoneAmount;
    float foodCarriedAmount;

    void dropFood();

    void pickFood();

    void visitColony();

    void putPheromones();

public:

    explicit Worker(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultHoursBeforeHunger(),
                Config::get()->getDefaultFoodConsumingTick(), currentCell, WorkerType),
            AgeAdult(Config::get()->getWorkerHoursBeforeAdult()) {
        this->pheromoneAmount = Config::get()->getMaxPheromoneAmount();
        this->foodCarriedAmount = 0;
    };

    bool eatFood(float amountToEat) override;

    void tickMove(Board *board) override;

};


#endif
