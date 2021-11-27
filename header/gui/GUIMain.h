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

public:
    explicit GUIMain(Board *board) { this->board = board; }

    int start();

    static void preventOutOfBorder(sf::RenderWindow *window, sf::View *simulationView,
                                   float zoom, sf::Vector2f *deltaPos);

    static sf::View getLetterboxView(sf::View view, float windowWidth, float windowHeight);
};


#endif
