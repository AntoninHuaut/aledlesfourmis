#include "../../header/core/SimulationStats.h"

void SimulationStats::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    states.transform *= getTransform();
    //states.texture = &tileSet;

    sf::Text text;
    text.setString(to_string(currentTPS));
    text.setFont(font);
    text.setCharacterSize(74);
    text.setFillColor(sf::Color::Red);

    target.draw(text);

}

void SimulationStats::setCurrentTps(int currentTps) {
    currentTPS = currentTps;
}

void SimulationStats::setWantedTps(int wantedTps) {
    wantedTPS = wantedTps;
}

void SimulationStats::setFoodAmount(int newFoodAmount) {
    SimulationStats::foodAmount = newFoodAmount;
}

void SimulationStats::setIsGameEnded(bool newIsGameEnded) {
    SimulationStats::isGameEnded = newIsGameEnded;
}

void SimulationStats::setWorkerAmount(int newWorkerAmount) {
    SimulationStats::workerAmount = newWorkerAmount;
}

void SimulationStats::setSoldierAmount(int newSoldierAmount) {
    SimulationStats::soldierAmount = newSoldierAmount;
}

void SimulationStats::setScoutAmount(int newScoutAmount) {
    SimulationStats::scoutAmount = newScoutAmount;
}

void SimulationStats::setSlaveOwnerAmount(int newSlaveOwnerAmount) {
    SimulationStats::slaveOwnerAmount = newSlaveOwnerAmount;
}
