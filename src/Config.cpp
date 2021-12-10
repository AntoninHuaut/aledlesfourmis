#include "../include/Config.h"

Config *Config::instance = nullptr;

Config *Config::get() {
    if (instance == nullptr) {
        instance = new Config();
    }
    return instance;
}

Config::Config() {
    std::cout << "Loading json configuration...";

    Json::Value data;
    std::ifstream i("../assets/config.json", std::ifstream::binary);
    i >> data;

    dev = data["dev"].asBool();

    tileSize = data["gui"]["tileSize"].asInt();
    marginOutOfBorder = data["gui"]["marginOutOfBorder"].asFloat();
    maxFps = data["gui"]["maxFps"].asInt();
    minFps = data["gui"]["minFps"].asInt();

    height = data["board"]["height"].asInt();
    length = data["board"]["length"].asInt();
    maxTps = data["board"]["maxTps"].asFloat();

    rockPercent = data["generation"]["rockPercent"].asFloat();
    foodPercent = data["generation"]["foodPercent"].asFloat();
    smallFoodUnitValue = data["generation"]["smallFoodUnit"].asFloat();
    bigFoodUnitValue = data["generation"]["bigFoodUnit"].asFloat();

    rockMaxAntOnCell = data["antOnCell"]["rock"].asInt();
    basicCellMaxAntOnCell = data["antOnCell"]["basic"].asInt();
    colonyMaxAntOnCell = data["antOnCell"]["colony"].asInt();

    defaultFoodConsumingTick = data["game"]["foodConsumption"]["default"].asFloat();
    queenFoodConsumingTick = data["game"]["foodConsumption"]["queen"].asFloat();

    defaultHoursBeforeDeath = data["game"]["hoursBeforeDeath"]["default"].asInt();
    queenHoursBeforeDeath = data["game"]["hoursBeforeDeath"]["queen"].asInt();

    scootHoursBeforeAdult = data["game"]["hoursBeforeAdult"]["scout"].asInt();
    workerHoursBeforeAdult = data["game"]["hoursBeforeAdult"]["worker"].asInt();

    defaultHoursBeforeHunger = data["game"]["hoursBeforeHunger"]["default"].asInt();
    slaveOwnerHoursBeforeHunger = data["game"]["hoursBeforeHunger"]["slaveOwner"].asInt();

    slaveOwnerMaxLarvaCanCarried = data["game"]["slaveOwner"]["maxLarvaCanCarried"].asInt();
    slaveOwnerMaxTickRandom = data["game"]["slaveOwner"]["maxTickRandom"].asInt();
    slaveOwnerMinTickRandom = data["game"]["slaveOwner"]["minTickRandom"].asInt();

    maxAntPheromoneAmount = data["game"]["pheromone"]["antAmount"].asFloat();
    maxAntPheromoneDropPercent = data["game"]["pheromone"]["dropPercent"].asFloat();
    pheromoneEvaporationPercent = data["game"]["pheromone"]["evaporationPercent"].asFloat();
    pheromoneSpreadPercent = data["game"]["pheromone"]["spreadPercent"].asFloat();
    maxPheromoneOnCell = data["game"]["pheromone"]["maxOnCell"].asFloat();

    defaultFoodColony = data["game"]["defaultFoodColony"].asFloat();
    newAntEveryDay = data["game"]["newAntEveryDay"].asInt();
    workerMaxFoodAmountCanCarried = data["game"]["workerMaxFoodAmountCanCarried"].asFloat();
    soldierHoursBeforeVisitColony = data["game"]["soldierHoursBeforeVisitColony"].asInt();
    soldierPercentToKillSlaveOwner = data["game"]["soldierPercentToKillSlaveOwner"].asFloat();

    std::cout << " OK" << std::endl;
}

int Config::getTileSize() const {
    return tileSize;
}

float Config::getMarginOutOfBorder() const {
    return marginOutOfBorder;
}

float Config::getHeightFloat() const {
    return static_cast<float>(height);
}

float Config::getLengthFloat() const {
    return static_cast<float>(length);
}

int Config::getHeight() const {
    return height;
}

int Config::getLength() const {
    return length;
}

float Config::getRockPercent() const {
    return rockPercent;
}

float Config::getFoodPercent() const {
    return foodPercent;
}

float Config::getSmallFoodUnitValue() const {
    return smallFoodUnitValue;
}

float Config::getBigFoodUnitValue() const {
    return bigFoodUnitValue;
}

int Config::getRockMaxAntOnCell() const {
    return rockMaxAntOnCell;
}

int Config::getBasicCellMaxAntOnCell() const {
    return basicCellMaxAntOnCell;
}

int Config::getColonyMaxAntOnCell() const {
    return colonyMaxAntOnCell;
}

float Config::getDefaultFoodConsumingTick() const {
    return defaultFoodConsumingTick;
}

float Config::getQueenFoodConsumingTick() const {
    return queenFoodConsumingTick;
}

int Config::getQueenHoursBeforeDeath() const {
    return queenHoursBeforeDeath;
}

int Config::getDefaultHoursBeforeDeath() const {
    return defaultHoursBeforeDeath;
}

int Config::getScootHoursBeforeAdult() const {
    return scootHoursBeforeAdult;
}

int Config::getWorkerHoursBeforeAdult() const {
    return workerHoursBeforeAdult;
}

int Config::getDefaultHoursBeforeHunger() const {
    return defaultHoursBeforeHunger;
}

int Config::getSlaveOwnerHoursBeforeHunger() const {
    return slaveOwnerHoursBeforeHunger;
}

float Config::getDefaultFoodColony() const {
    return defaultFoodColony;
}

int Config::getSlaveOwnerMaxLarvaCanCarried() const {
    return slaveOwnerMaxLarvaCanCarried;
}

int Config::getSlaveOwnerMinTickRandom() const {
    return slaveOwnerMinTickRandom;
}

int Config::getSlaveOwnerMaxTickRandom() const {
    return slaveOwnerMaxTickRandom;
}

int Config::getNewAntEveryDay() const {
    return newAntEveryDay;
}

float Config::getWorkerMaxFoodAmountCanCarried() const {
    return workerMaxFoodAmountCanCarried;
}

int Config::getSoldierHoursBeforeVisitColony() const {
    return soldierHoursBeforeVisitColony;
}

float Config::getMaxTps() const {
    return maxTps;
}

int Config::getMaxFps() const {
    return maxFps;
}

float Config::getMaxAntPheromoneAmount() const {
    return maxAntPheromoneAmount;
}

float Config::getMaxAntPheromoneDropPercent() const {
    return maxAntPheromoneDropPercent;
}

float Config::getPheromoneEvaporationPercent() const {
    return pheromoneEvaporationPercent;
}

float Config::getPheromoneSpreadPercent() const {
    return pheromoneSpreadPercent;
}

float Config::getSoldierPercentToKillSlaveOwner() const {
    return soldierPercentToKillSlaveOwner;
}

int Config::getMinFps() const {
    return minFps;
}

float Config::getMaxPheromoneOnCell() const {
    return maxPheromoneOnCell;
}

bool Config::isDev() const {
    return dev;
}
