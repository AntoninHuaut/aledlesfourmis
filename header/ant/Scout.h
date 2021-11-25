#ifndef ANT_SCOUT_H
#define ANT_SCOUT_H

#include "Ant.h"
#include "AntAge.h"
#include "../Config.h"

class Scout : public Ant, public AntAge {

public:
    explicit Scout(BoardCell *currentCell) :
            Ant(Config::get()->getDefaultHoursBeforeDeath(), Config::get()->getDefaultFoodConsumingTick(), currentCell),
            AntAge(Config::get()->getScootHoursBeforeAdult()) {};

};


#endif
