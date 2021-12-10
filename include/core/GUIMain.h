#ifndef ANT_GUIMAIN_H
#define ANT_GUIMAIN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../map/Board.h"
#include "../core/Game.h"
#include "../Config.h"

class SimulationStats;

struct threadData {
    sf::RenderWindow *window;
    sf::Mutex *mutex;
    sf::View *simView;
    sf::View *statView;
    SimulationStats *stats;
    Board *board;
    Game *game;
} typedef threadData;

class GUIMain {

    Board *board;
    Game *game;
    SimulationStats *stats;
    bool waitReleaseGameKey = false;

    sf::RenderWindow *window;
    sf::View simView;
    sf::View statView;

    sf::Vector2f oldPos;
    bool moving = false;
    float zoom = 1;
    float currentZoom = zoom;

    void runUI(sf::Mutex *mutex);

    void smoothOnKeyPressed();

    void onClosed();

    void onMouseButtonPressed(sf::Event event);

    void onMouseButtonReleased(sf::Event event);

    void onMouseMoved(sf::Event event);

    void onMouseWheelScrolled(sf::Event event);

    void onResized(sf::Event event);

    void center();

    void preventOutOfBorder(sf::Vector2f deltaPos);

    void letterBoxView(float windowWidth, float windowHeight);

    static sf::Vector2f getMapSize();

public:

    explicit GUIMain(sf::Mutex *mutex, Game *game, Board *board, SimulationStats *stats) {
        this->game = game;
        this->board = board;
        this->stats = stats;
        this->window = new sf::RenderWindow(sf::VideoMode(1200, 900), "Ant Simulation");

        runUI(mutex);
    }
};


#endif
