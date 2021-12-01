#ifndef ANT_SLAVEOWNER_H
#define ANT_SLAVEOWNER_H

#include "Ant.h"
#include "../Config.h"

using namespace std;

class Board;

class SlaveOwner : public Ant {

    int larvaCarried = 0;
    bool haveArrivedToCenter = false;

public:

    explicit SlaveOwner(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), 10, Config::get()->getDefaultFoodConsumingTick(),
                currentCell, SlaveOwnerType) {};

    void goToCenter(Board *board);

    void tickMove(Board *board) override;

    bool hasEatFood(double amountToEat) override;

};


#endif
