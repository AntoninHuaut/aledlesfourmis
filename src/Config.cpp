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

    std::ifstream i("../assets/config.json");
    json data;
    i >> data;

    height = data["board"]["height"];
    length = data["board"]["length"];

    rockPercent = data["generation"]["rockPercent"];
    foodPercent = data["generation"]["foodPercent"];
    smallFoodUnitValue = data["generation"]["smallFoodUnit"];
    bigFoodUnitValue = data["generation"]["bigFoodUnit"];

    rockMaxAntOnCell = data["antOnCell"]["rock"];
    basicCellMaxAntOnCell = data["antOnCell"]["basic"];
    colonyMaxAntOnCell = data["antOnCell"]["colony"];

    defaultFoodConsumingTick = data["ant"]["foodConsumption"]["default"];
    queenFoodConsumingTick = data["ant"]["foodConsumption"]["queen"];

    queenHoursBeforeDeath = data["ant"]["hoursBeforeDeath"]["default"];
    defaultHoursBeforeDeath = data["ant"]["hoursBeforeDeath"]["queen"];

    scootHoursBeforeAdult = data["ant"]["hoursBeforeAdult"]["worker"];
    workerHoursBeforeAdult = data["ant"]["hoursBeforeAdult"]["scout"];

    newAntEveryDay = data["ant"]["newAntEveryDay"];
    workerMaxFoodAmountCanCarried = data["ant"]["workerMaxFoodAmountCanCarried"];
    soldierHoursBeforeVisitColony = data["ant"]["soldierHoursBeforeVisitColony"];
    slaveOwnerHoursBeforeHunger = data["ant"]["slaveOwnerHoursBeforeHunger"];

    std::cout << " OK" << std::endl;
}

int Config::getHeight() const {
    return height;
}

int Config::getLength() const {
    return length;
}

double Config::getRockPercent() const {
    return rockPercent;
}

double Config::getFoodPercent() const {
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

double Config::getDefaultFoodConsumingTick() const {
    return defaultFoodConsumingTick;
}

double Config::getQueenFoodConsumingTick() const {
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
