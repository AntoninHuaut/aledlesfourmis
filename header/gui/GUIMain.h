#ifndef ANT_GUIMAIN_H
#define ANT_GUIMAIN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../map/Board.h"
#include "../Config.h"

struct threadData {
    sf::RenderWindow *window;
    Board *board;
} typedef threadData;

class GUIMain {

    Board *board;
    sf::RenderWindow *window;
    sf::View simView;

    sf::Vector2f oldPos;
    bool moving = false;
    float zoom = 1;
    float currentZoom = zoom;

    void runUI();

public:

    explicit GUIMain(Board *board) {
        this->board = board;
        this->window = new sf::RenderWindow(sf::VideoMode(1200, 900), "Ant Simulation");

        runUI();
    }

    void onClosed();

    void onMouseButtonPressed(sf::Event event);

    void onMouseButtonReleased(sf::Event event);

    void onMouseMoved(sf::Event event);

    void onMouseWheelScrolled(sf::Event event);

    void onResized(sf::Event event);

    void preventOutOfBorder(sf::Vector2f *deltaPos);

    void letterBoxView(float windowWidth, float windowHeight);
};


#endif
