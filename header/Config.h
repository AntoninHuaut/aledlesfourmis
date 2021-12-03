#ifndef ANT_CONFIG_H
#define ANT_CONFIG_H

#include "./lib/json.h"
#include <fstream>
#include <iostream>

class Config {

    static Config *instance;

    int tileSize;
    float marginOutOfBorder;

    int height;
    int length;
    float maxTps;

    float rockPercent;
    float foodPercent;
    int smallFoodUnitValue;
    int bigFoodUnitValue;

    int rockMaxAntOnCell;
    int basicCellMaxAntOnCell;
    int colonyMaxAntOnCell;

    float defaultFoodConsumingTick;
    float queenFoodConsumingTick;

    int queenHoursBeforeDeath;
    int defaultHoursBeforeDeath;

    int scootHoursBeforeAdult;
    int workerHoursBeforeAdult;

    float defaultFoodColony;
    int newAntEveryDay;
    float workerMaxFoodAmountCanCarried;
    int soldierHoursBeforeVisitColony;
    int slaveOwnerHoursBeforeHunger;

protected:
    Config();

public:

    Config(Config &other) = delete; // Singletons should not be cloneable

    void operator=(const Config &) = delete; // Singletons should not be assignable

    static Config *get();

    int getTileSize() const;

    float getMarginOutOfBorder() const;

    float getHeightFloat() const;

    float getLengthFloat() const;

    int getHeight() const;

    int getLength() const;

    float getMaxTps() const;

    float getRockPercent() const;

    float getFoodPercent() const;

    int getSmallFoodUnitValue() const;

    int getBigFoodUnitValue() const;

    int getRockMaxAntOnCell() const;

    int getBasicCellMaxAntOnCell() const;

    int getColonyMaxAntOnCell() const;

    float getDefaultFoodConsumingTick() const;

    float getQueenFoodConsumingTick() const;

    int getQueenHoursBeforeDeath() const;

    int getDefaultHoursBeforeDeath() const;

    int getScootHoursBeforeAdult() const;

    int getWorkerHoursBeforeAdult() const;

    float getDefaultFoodColony() const;

    int getNewAntEveryDay() const;

    float getWorkerMaxFoodAmountCanCarried() const;

    int getSoldierHoursBeforeVisitColony() const;

    int getSlaveOwnerHoursBeforeHunger() const;

};

#endif
