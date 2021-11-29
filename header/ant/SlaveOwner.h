#ifndef ANT_SLAVEOWNER_H
#define ANT_SLAVEOWNER_H

#include "Ant.h"
#include "../Config.h"

using namespace std;

class Board;

class SlaveOwner : public Ant {

    int larvaCarried = 0;

public:

    explicit SlaveOwner(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultFoodConsumingTick(),
                currentCell, SlaveOwnerType) {};

    void goToCenter(Board *board);

    void tick(Board *board) override;

};


#endif
