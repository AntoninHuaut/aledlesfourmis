#include "../../header/map/Board.h"


int getTileNumber(BoardCell *cell) {

    switch (cell->getBoardCellType()) {

        case RockCellType:
            return ROCK_FLOOR;

        default:
            return BASIC_FLOOR + (cell->getRandomCellDecoration());
    }
}

bool Board::render() {

    if (!m_tileset.loadFromFile("./assets/tileset.png"))
        return false;

    int width = Config::get()->getLength();
    int height = Config::get()->getHeight();
    sf::Vector2u tileSize = sf::Vector2u(32, 32);

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);


    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j) {
            // get the current tile number
            int tileNumber = getTileNumber(cells[j][i]);

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }


    return true;

}