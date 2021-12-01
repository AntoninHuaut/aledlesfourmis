#include "../../header/map/Board.h"
#include "../../header/map/BoardGenerator.h"


void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

bool Board::calcRender() {
    int maxLength = Config::get()->getLength();
    int maxHeight = Config::get()->getHeight();
    sf::Vector2u tileSize = sf::Vector2u(Config::get()->getTileSize(), Config::get()->getTileSize());

    int verticeSize = maxLength * maxHeight * 4;

    // create new vertex array
    sf::VertexArray tmpVertex(sf::Quads, verticeSize);

    auto *cellsWithOtherLayer = new list<BoardCell *>;

    for (int height = 0; height < maxHeight; ++height) {
        for (int length = 0; length < maxLength; ++length) {

            // Cells with multiple layers
            if (cells[height][length]->numberOfLayers() >= 2) {
                cellsWithOtherLayer->push_back(cells[height][length]);
            }

            // get the current tile number
            int tileNumber = cells[height][length]->getFloorTileNumber();

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex *quad = &tmpVertex[(length + (height * maxLength)) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(length * tileSize.x, height * tileSize.y);
            quad[1].position = sf::Vector2f((length + 1) * tileSize.x, height * tileSize.y);
            quad[2].position = sf::Vector2f((length + 1) * tileSize.x, (height + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(length * tileSize.x, (height + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }


    for (auto const &cell: *cellsWithOtherLayer) {

        for (auto const &tileNumber: *cell->getOtherLayerTileNumbers()) {

            verticeSize += 4;
            tmpVertex.resize(verticeSize);
            sf::Vertex *quad = &tmpVertex[verticeSize - 4];

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            int i = cell->getPosHeight();
            int j = cell->getPosLength();

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

    m_vertices = tmpVertex;

    return true;
}

list<BoardCell *> *Board::getNearbyCells(BoardCell *cell) {

    auto *nearbyCells = new list<BoardCell *>;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int tmpHeight = cell->getPosHeight() + i;
            int tmpLength = cell->getPosLength() + j;
            if (tmpHeight < 0 || tmpLength < 0 || tmpHeight >= Config::get()->getHeight() ||
                tmpLength >= Config::get()->getLength()) {
                continue;
            }

            if (this->cells[tmpHeight][tmpLength] != nullptr) {
                nearbyCells->push_back(this->cells[tmpHeight][tmpLength]);
            }
        }
    }

    return nearbyCells;
}

BoardCell *Board::getCenterCell() {
    return cells[Config::get()->getHeight() / 2][Config::get()->getLength() / 2];
}