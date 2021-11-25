#ifndef ANT_GUIMAIN_H
#define ANT_GUIMAIN_H

#include <SFML/Graphics.hpp>
#include <iostream>
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

    static void preventOutOfBorder(sf::RenderWindow *window, sf::View *simulationView,
                                   float zoom, sf::Vector2f *deltaPos);

    int start();
};


#endif
