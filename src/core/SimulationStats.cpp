#include <iostream>
#include "../../include/core/SimulationStats.h"
#include <iomanip>
#include <sstream>
#include <list>
#include "../../include/core/InfoDisplay.h"
#include "../../include/core/TileEnum.h"

sf::Vector2f SimulationStats::viewSize = {0, 0};

void SimulationStats::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &tileSet;

    sf::Vector2f viewScale(2, 1);

    if (viewSize.x == 0 && viewSize.y == 0) {
        sf::Vector2<unsigned int> windowSize = target.getSize();
        viewSize = sf::Vector2f(windowSize.x, windowSize.y);
    }

    float displayHeight = viewSize.x;
    float displayWidth = viewSize.y;


    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(0.f, 0.f);
    quad[1].position = sf::Vector2f(displayWidth, 0.f);
    quad[2].position = sf::Vector2f(displayWidth, displayHeight);
    quad[3].position = sf::Vector2f(0.f, displayHeight);

    quad[0].color = sf::Color(0, 0, 0, 170);
    quad[1].color = sf::Color(0, 0, 0, 170);
    quad[2].color = sf::Color(0, 0, 0, 170);
    quad[3].color = sf::Color(0, 0, 0, 170);


    target.draw(quad);
    int minFontSize = 14;
    int fontSize = max(min(static_cast<int>(displayHeight / 10), static_cast<int>(displayWidth / 10)), minFontSize);

    cout << target.getSize().y << endl;
    cout << displayHeight << endl;

    sf::Text text;
    stringstream fAmountStream;
    fAmountStream << std::fixed << std::setprecision(2) << foodAmount;

    text.setString(fAmountStream.str());
    text.setFont(font);
    text.setScale(viewScale.x, viewScale.y);
    text.setPosition(100, displayHeight / 2 - fontSize / 2);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::Red);

    string textToDisplay = fAmountStream.str();

    list<InfoDisplay *> statsLines;
    statsLines.push_back(new InfoDisplay(textToDisplay, FOOD_LAYER, tileSet, font, viewScale));
    statsLines.push_back(new InfoDisplay(to_string(scoutAmount), SCOOT_ANT, tileSet, font, viewScale));
    statsLines.push_back(new InfoDisplay(to_string(workerAmount), WORKER_ANT, tileSet, font, viewScale));
    statsLines.push_back(new InfoDisplay(to_string(soldierAmount), SOLDIER_ANT, tileSet, font, viewScale));
    statsLines.push_back(new InfoDisplay(to_string(slaveOwnerAmount), SLAVEOWNER_ANT, tileSet, font, viewScale));


    float spaceBetweenLines = displayHeight / 7;

    sf::Transform t;
    for (auto line: statsLines) {
        target.draw(*line, states);
        t.translate(0, spaceBetweenLines);
        states.transform = t;

        delete line;
    }

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
