#ifndef ANT_SCOUT_H
#define ANT_SCOUT_H

#include "Ant.h"
#include "AgeAdult.h"
#include "../Config.h"

class Scout : public Ant, public AgeAdult {

public:
    explicit Scout(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultHoursBeforeHunger(),
                Config::get()->getDefaultFoodConsumingTick(), currentCell, ScoutType),
            AgeAdult(Config::get()->getScootHoursBeforeAdult()) {};

    void tickMove(Board *board) override;


};


#endif
