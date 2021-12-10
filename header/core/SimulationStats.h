#ifndef ANT_SIMULATIONSTATS_H
#define ANT_SIMULATIONSTATS_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class SimulationStats : public sf::Drawable, public sf::Transformable {

    int currentTPS = 0;
    int wantedTPS = 0;

    float foodAmount = 0;

    bool isGameEnded = false;
    string endMessage;

    int workerAmount = 0;
    int soldierAmount = 0;
    int scoutAmount = 0;
    int slaveOwnerAmount = 0;

    sf::Texture tileSet;
    sf::Font font;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:

    SimulationStats() {
        tileSet.loadFromFile("./assets/tileset.png");
        font.loadFromFile("./assets/Roboto.ttf");
    }

    void setCurrentTps(int currentTps);

    void setWantedTps(int wantedTps);

    void setFoodAmount(float newFoodAmount);

    void setIsGameEnded(bool newIsGameEnded);

    void setWorkerAmount(int newWorkerAmount);

    void setSoldierAmount(int newSoldierAmount);

    void setScoutAmount(int newScoutAmount);

    void setSlaveOwnerAmount(int newSlaveOwnerAmount);

};


#endif
