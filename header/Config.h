#ifndef ANT_CONFIG_H
#define ANT_CONFIG_H

#include "./lib/json.h"
#include <fstream>
#include <iostream>

class Config {

    static Config *instance;

    int height;
    int length;

    double rockPercent;
    double foodPercent;
    int smallFoodUnitValue;
    int bigFoodUnitValue;

    int rockMaxAntOnCell;
    int basicCellMaxAntOnCell;
    int colonyMaxAntOnCell;

    double defaultFoodConsumingTick;
    double queenFoodConsumingTick;

    int queenHoursBeforeDeath;
    int defaultHoursBeforeDeath;

    int scootHoursBeforeAdult;
    int workerHoursBeforeAdult;

    int newAntEveryDay;
    int workerMaxFoodAmountCanCarried;
    int soldierHoursBeforeVisitColony;
    int slaveOwnerHoursBeforeHunger;

protected:
    Config();

public:

    Config(Config &other) = delete; // Singletons should not be cloneable

    void operator=(const Config &) = delete; // Singletons should not be assignable

    static Config *get();

    int getHeight() const;

    int getLength() const;

    double getRockPercent() const;

    double getFoodPercent() const;

    int getSmallFoodUnitValue() const;

    int getBigFoodUnitValue() const;

    int getRockMaxAntOnCell() const;

    int getBasicCellMaxAntOnCell() const;

    int getColonyMaxAntOnCell() const;

    double getDefaultFoodConsumingTick() const;

    double getQueenFoodConsumingTick() const;

    int getQueenHoursBeforeDeath() const;

    int getDefaultHoursBeforeDeath() const;

    int getScootHoursBeforeAdult() const;

    int getWorkerHoursBeforeAdult() const;

    int getNewAntEveryDay() const;

    int getWorkerMaxFoodAmountCanCarried() const;

    int getSoldierHoursBeforeVisitColony() const;

    int getSlaveOwnerHoursBeforeHunger() const;

};

#endif
