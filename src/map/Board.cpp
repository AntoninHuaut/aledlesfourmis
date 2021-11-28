#include "../../header/map/Board.h"

bool Board::render() {

    if (!m_tileset.loadFromFile("./assets/tileset.png"))
        return false;

    int width = Config::get()->getLength();
    int height = Config::get()->getHeight();
    sf::Vector2u tileSize = sf::Vector2u(Config::get()->getTileSize(), Config::get()->getTileSize());

    int vertriceSize = width * height * 4;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(vertriceSize);

    auto *cellsWithOtherLayer = new list<BoardCell *>;

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {

            // Cells with multiple layers
            if (cells[i][j]->numberOfLayers() >= 2) {
                cellsWithOtherLayer->push_back(cells[i][j]);
            }

            // get the current tile number
            int tileNumber = cells[i][j]->getFloorTileNumber();

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex *quad = &m_vertices[(j + i * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
            quad[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
            quad[2].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }


    for (auto const &cell: *cellsWithOtherLayer) {

        for (auto const &tileNumber: *cell->getOtherLayerTileNumbers()) {

            vertriceSize += 4;
            m_vertices.resize(vertriceSize);
            sf::Vertex *quad = &m_vertices[vertriceSize - 4];

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            int j = cell->getPosHeight();
            int i = cell->getPosLength();

            // define its 4 corners
            quad[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
            quad[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
            quad[2].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        }

    }

    return true;
}