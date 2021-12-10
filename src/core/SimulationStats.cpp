#include <iostream>
#include <cmath>
#include "../../include/core/SimulationStats.h"
#include <iomanip>
#include <sstream>

void SimulationStats::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    //states.texture = &tileSet;
    float displayHeight = 150;

    sf::Vector2<unsigned int> windowSize = target.getSize();

    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(0.f, 0.f);
    quad[1].position = sf::Vector2f(static_cast<float>(windowSize.x), 0.f);
    quad[2].position = sf::Vector2f(static_cast<float>(windowSize.x), displayHeight);
    quad[3].position = sf::Vector2f(0.f, displayHeight);

    quad[0].color = sf::Color(0, 0, 0, 170);
    quad[1].color = sf::Color(0, 0, 0, 170);
    quad[2].color = sf::Color(0, 0, 0, 170);
    quad[3].color = sf::Color(0, 0, 0, 170);

    //sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));

    target.draw(quad);

    int fontSize = min(windowSize.x / 20, windowSize.y / 20);

    cout << target.getSize().x << endl;

    sf::Text text;
    stringstream fAmountStream;
    fAmountStream << std::fixed << std::setprecision(2) << foodAmount;

    text.setString(fAmountStream.str());
    text.setFont(font);
    text.setPosition(100, displayHeight / 2 - fontSize / 2);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::Red);

    target.draw(text);
}

void SimulationStats::setCurrentTps(int currentTps) {
    currentTPS = currentTps;
}

void SimulationStats::setWantedTps(int wantedTps) {
    wantedTPS = wantedTps;
}

void SimulationStats::setFoodAmount(float newFoodAmount) {
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
