#ifndef ANT_CONFIG_H
#define ANT_CONFIG_H

#include "./lib/json.h"
#include <fstream>
#include <iostream>

class Config {

    static Config *instance;

    int tileSize;
    float marginOutOfBorder;
    float maxFps;
    float minFps;
    int saveGNUDataEveryXTps;

    int height;
    int length;
    float maxTps;

    float rockPercent;
    float foodPercent;
    float smallFoodUnitValue;
    float bigFoodUnitValue;

    int rockMaxAntOnCell;
    int basicCellMaxAntOnCell;
    int colonyMaxAntOnCell;

    float defaultFoodConsumingTick;
    float queenFoodConsumingTick;

    int queenHoursBeforeDeath;
    int defaultHoursBeforeDeath;

    int scootHoursBeforeAdult;
    int workerHoursBeforeAdult;

    int defaultHoursBeforeHunger;
    int slaveOwnerHoursBeforeHunger;

    int slaveOwnerMaxLarvaCanCarried;
    int slaveOwnerMinTickRandom;
    int slaveOwnerMaxTickRandom;

    float maxAntPheromoneAmount;
    float maxAntPheromoneDropPercent;
    float pheromoneEvaporationPercent;
    float pheromoneSpreadPercent;
    float maxPheromoneOnCell;

    float defaultFoodColony;
    int newAntEveryDay;
    float workerMaxFoodAmountCanCarried;
    int soldierHoursBeforeVisitColony;
    float soldierPercentToKillSlaveOwner;

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

    float getMaxFps() const;

    float getMinFps() const;

    float getRockPercent() const;

    float getFoodPercent() const;

    float getSmallFoodUnitValue() const;

    float getBigFoodUnitValue() const;

    int getRockMaxAntOnCell() const;

    int getBasicCellMaxAntOnCell() const;

    int getColonyMaxAntOnCell() const;

    float getDefaultFoodConsumingTick() const;

    float getQueenFoodConsumingTick() const;

    int getQueenHoursBeforeDeath() const;

    int getDefaultHoursBeforeDeath() const;

    int getScootHoursBeforeAdult() const;

    int getWorkerHoursBeforeAdult() const;

    int getDefaultHoursBeforeHunger() const;

    int getSlaveOwnerHoursBeforeHunger() const;

    int getSlaveOwnerMaxLarvaCanCarried() const;

    int getSlaveOwnerMinTickRandom() const;

    int getSlaveOwnerMaxTickRandom() const;

    float getMaxAntPheromoneAmount() const;

    float getMaxAntPheromoneDropPercent() const;

    float getPheromoneEvaporationPercent() const;

    float getPheromoneSpreadPercent() const;

    float getMaxPheromoneOnCell() const;

    float getDefaultFoodColony() const;

    int getNewAntEveryDay() const;

    float getWorkerMaxFoodAmountCanCarried() const;

    int getSoldierHoursBeforeVisitColony() const;

    float getSoldierPercentToKillSlaveOwner() const;

    int getSaveGnuDataEveryXTps() const;

};

#endif
