#ifndef ANT_BOARD_H
#define ANT_BOARD_H

#include "BoardCell.h"
#include <SFML/Graphics.hpp>
#include "../Config.h"

using namespace std;

class Board : public sf::Drawable, public sf::Transformable {

    BoardCell ***cells;
//    list<ColonyCell*> coloniesCells;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

public:
    explicit Board(BoardCell ***cells/*, list<ColonyCell*> coloniesCells*/) {
        this->cells = cells;
//        this->coloniesCells = coloniesCells;

    };

    BoardCell ***getCells() { return cells; }

    list<BoardCell *> getNearbyCells(BoardCell *cell);

    bool render();
};

#endif