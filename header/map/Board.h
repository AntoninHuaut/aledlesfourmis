#ifndef ANT_BOARD_H
#define ANT_BOARD_H

#include <random>
#include <SFML/Graphics.hpp>
#include "BoardCell.h"
#include "BasicCell.h"
#include "ColonyCell.h"
#include "../Config.h"
#include "../core/TileEnum.h"

using namespace std;

class Queen;

class Board : public sf::Drawable, public sf::Transformable {

    BoardCell ***cells;
    list<ColonyCell *> *coloniesCells;
    int currentTick = 0;

    list<Ant *> *antList;
    Queen *antQueen;

    sf::VertexArray floor_vertex;
    sf::VertexArray layer_vertex;


    sf::Texture m_tileset;

    bool windowClosed = false;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    BasicCell *findExpandableBasicCell();

public:
    explicit Board(BoardCell ***cells);

    ~Board();

    int getCurrentTick() const { return currentTick; }

    void incrementCurrentTick() { currentTick++; }

    bool isWindowClosed() const { return windowClosed; }

    void setWindowClosed(bool newWindowClosed) {
        this->windowClosed = newWindowClosed;
    }

    bool isQueenAlive() {
        return antQueen != nullptr;
    }

    BoardCell ***getCells() { return cells; }

    list<BoardCell *> getNearbyCells(BoardCell *cell);

    list<BoardCell *> getNearbyCells(int height, int length);

    list<BoardCell *> getNearbyRocks(BoardCell *cell);

    bool calcRender();

    list<ColonyCell *> *getColoniesCells() const {
        return coloniesCells;
    }

    void addColoniesCell(ColonyCell *newColoniesCells) {
        coloniesCells->push_back(newColoniesCells);
    }

    list<Ant *> *getAntList() const {
        return antList;
    }

    void addAntList(Ant *ant) {
        antList->push_back(ant);
    }

    Queen *getAntQueen() const {
        return antQueen;
    }

    void setAntQueen(Queen *newAntQueen) {
        antQueen = newAntQueen;
    }

    BoardCell *getCenterCell();

    void expandColonies();
};

#endif