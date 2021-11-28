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
        this->cells = cells;
    };

    BoardCell ***getCells() { return cells; }

    list<ColonyCell *> *getColoniesCells() const;

    void addColoniesCell(ColonyCell *newColoniesCells);

    list<BoardCell *> getNearbyCells(BoardCell *cell);

    bool render();
};

#endif