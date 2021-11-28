#ifndef ANT_BOARD_H
#define ANT_BOARD_H

#include "BoardCell.h"
#include "ColonyCell.h"
#include <SFML/Graphics.hpp>
#include "../Config.h"
#include "../gui/TileEnum.h"

using namespace std;

class Board : public sf::Drawable, public sf::Transformable {

    BoardCell ***cells;
    list<ColonyCell *> *coloniesCells;

    list<Ant *> *antList;
    Ant *antQueen;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

public:
    explicit Board(BoardCell ***cells) {
        this->coloniesCells = new list<ColonyCell *>;
        this->antList = new list<Ant *>;
        this->cells = cells;
    };

    BoardCell ***getCells() { return cells; }

    list<BoardCell *> getNearbyCells(BoardCell *cell);

    bool render();

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

    Ant *getAntQueen() const {
        return antQueen;
    }

    void setAntQueen(Ant *newAntQueen) {
        antQueen = newAntQueen;
    }
};

#endif