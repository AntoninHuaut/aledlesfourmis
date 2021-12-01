#ifndef ANT_BOARD_H
#define ANT_BOARD_H

#include "BoardCell.h"
#include "ColonyCell.h"
#include <SFML/Graphics.hpp>
#include "../Config.h"
#include "../core/TileEnum.h"

using namespace std;

class Queen;

class Board : public sf::Drawable, public sf::Transformable {

    BoardCell ***cells;
    list<ColonyCell *> *coloniesCells;

    list<Ant *> *antList;
    Queen *antQueen;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    bool windowClosed = false;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    explicit Board(BoardCell ***cells) {
        this->coloniesCells = new list<ColonyCell *>;
        this->antList = new list<Ant *>;
        this->cells = cells;
        this->antQueen = nullptr;

        m_tileset.loadFromFile("./assets/tileset.png");
    };

    bool isWindowClosed() const { return windowClosed; }

    void setWindowClosed(bool newWindowClosed) {
        this->windowClosed = newWindowClosed;
    }

    bool isQueenAlive() {
        return antQueen != nullptr;
    }

    BoardCell ***getCells() { return cells; }

    list<BoardCell *> *getNearbyCells(BoardCell *cell);

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

};

#endif