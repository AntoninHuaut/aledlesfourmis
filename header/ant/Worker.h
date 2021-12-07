#ifndef ANT_WORKER_H
#define ANT_WORKER_H

#include "Ant.h"
#include "AgeAdult.h"
#include "../Config.h"

class Worker : public Ant, public AgeAdult {

    bool goingHome = false;

    float pheromoneAmount;
    float foodCarriedAmount;
    sf::Vector2i direction = sf::Vector2i(0, 0);

    void dropFood();

    void pickFood();

    void visitColony();

    void putPheromones();

    void goCollectFood(Board *board);

    BoardCell *getNextCellToFood(Board *board, const list<BoardCell *> &availableCells);

    list<BoardCell *> getDirectionalCells(Board *board, const list<BoardCell *> &availableCells);

    BoardCell *getCellWithMaxPheromoneOrRandom(list<BoardCell *> cells);

public:

    explicit Worker(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultHoursBeforeHunger(),
                Config::get()->getDefaultFoodConsumingTick(), currentCell, WorkerType),
            AgeAdult(Config::get()->getWorkerHoursBeforeAdult()) {
        this->pheromoneAmount = Config::get()->getMaxAntPheromoneAmount();
        this->foodCarriedAmount = 0;
    };

    bool eatFood(float amountToEat) override;

    void tickMove(Board *board) override;

};


#endif
