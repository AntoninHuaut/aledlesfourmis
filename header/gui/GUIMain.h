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

    int start();
};


#endif
