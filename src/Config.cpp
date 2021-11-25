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

    height = data["board"]["height"].asInt();
    length = data["board"]["length"].asInt();
    tileSize = data["board"]["tileSize"].asFloat();
    marginOutOfBorder = data["board"]["marginOutOfBorder"].asFloat();

    rockPercent = data["generation"]["rockPercent"].asFloat();
    foodPercent = data["generation"]["foodPercent"].asFloat();
    smallFoodUnitValue = data["generation"]["smallFoodUnit"].asInt();
    bigFoodUnitValue = data["generation"]["bigFoodUnit"].asInt();

    rockMaxAntOnCell = data["antOnCell"]["rock"].asInt();
    basicCellMaxAntOnCell = data["antOnCell"]["basic"].asInt();
    colonyMaxAntOnCell = data["antOnCell"]["colony"].asInt();

    defaultFoodConsumingTick = data["ant"]["foodConsumption"]["default"].asFloat();
    queenFoodConsumingTick = data["ant"]["foodConsumption"]["queen"].asFloat();

    queenHoursBeforeDeath = data["ant"]["hoursBeforeDeath"]["default"].asInt();
    defaultHoursBeforeDeath = data["ant"]["hoursBeforeDeath"]["queen"].asInt();

    scootHoursBeforeAdult = data["ant"]["hoursBeforeAdult"]["worker"].asInt();
    workerHoursBeforeAdult = data["ant"]["hoursBeforeAdult"]["scout"].asInt();

    newAntEveryDay = data["ant"]["newAntEveryDay"].asInt();
    workerMaxFoodAmountCanCarried = data["ant"]["workerMaxFoodAmountCanCarried"].asInt();
    soldierHoursBeforeVisitColony = data["ant"]["soldierHoursBeforeVisitColony"].asInt();
    slaveOwnerHoursBeforeHunger = data["ant"]["slaveOwnerHoursBeforeHunger"].asInt();

    std::cout << " OK" << std::endl;
}

int Config::getHeight() const {
    return height;
}

int Config::getLength() const {
    return length;
}

float Config::getTileSize() const {
    return tileSize;
}

float Config::getMarginOutOfBorder() const {
    return marginOutOfBorder;
}

float Config::getRockPercent() const {
    return rockPercent;
}

float Config::getFoodPercent() const {
    return foodPercent;
}

int Config::getSmallFoodUnitValue() const {
    return smallFoodUnitValue;
}

int Config::getBigFoodUnitValue() const {
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

int Config::getNewAntEveryDay() const {
    return newAntEveryDay;
}

int Config::getWorkerMaxFoodAmountCanCarried() const {
    return workerMaxFoodAmountCanCarried;
}

int Config::getSoldierHoursBeforeVisitColony() const {
    return soldierHoursBeforeVisitColony;
}

int Config::getSlaveOwnerHoursBeforeHunger() const {
    return slaveOwnerHoursBeforeHunger;
}
