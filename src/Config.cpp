#include "../header/Config.h"

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

    tileSize = data["gui"]["tileSize"].asInt();
    marginOutOfBorder = data["gui"]["marginOutOfBorder"].asFloat();

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

    defaultFoodConsumingTick = data["ant"]["foodConsumption"]["default"].asFloat();
    queenFoodConsumingTick = data["ant"]["foodConsumption"]["queen"].asFloat();

    defaultHoursBeforeDeath = data["ant"]["hoursBeforeDeath"]["default"].asInt();
    queenHoursBeforeDeath = data["ant"]["hoursBeforeDeath"]["queen"].asInt();

    scootHoursBeforeAdult = data["ant"]["hoursBeforeAdult"]["scout"].asInt();
    workerHoursBeforeAdult = data["ant"]["hoursBeforeAdult"]["worker"].asInt();

    defaultHoursBeforeHunger = data["ant"]["hoursBeforeHunger"]["default"].asInt();
    slaveOwnerHoursBeforeHunger = data["ant"]["hoursBeforeHunger"]["slaveOwner"].asInt();

    slaveOwnerMaxLarvaCanCarried = data["ant"]["slaveOwner"]["maxLarvaCanCarried"].asInt();
    slaveOwnerMaxTickRandom = data["ant"]["slaveOwner"]["maxTickRandom"].asInt();
    slaveOwnerMinTickRandom = data["ant"]["slaveOwner"]["minTickRandom"].asInt();

    defaultFoodColony = data["ant"]["defaultFoodColony"].asFloat();
    newAntEveryDay = data["ant"]["newAntEveryDay"].asInt();
    workerMaxFoodAmountCanCarried = data["ant"]["workerMaxFoodAmountCanCarried"].asFloat();
    soldierHoursBeforeVisitColony = data["ant"]["soldierHoursBeforeVisitColony"].asInt();

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
