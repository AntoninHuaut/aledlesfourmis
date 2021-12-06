#ifndef ANT_SOLDIER_H
#define ANT_SOLDIER_H

#include "Ant.h"
#include "../Config.h"

class Soldier : public Ant {

    int tickSinceColonyVisited = 0;
    
public:
    explicit Soldier(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultHoursBeforeHunger(),
                Config::get()->getDefaultFoodConsumingTick(), currentCell, SoldierType) {};

    void moveSoldier(Board *board);

    void tickMove(Board *board) override;

    static bool attackOneSlaveOwnerNearCell(Board *board, BoardCell *cell);
};


#endif
