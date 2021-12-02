#include "../../header/map/Board.h"
#include "../../header/map/BoardGenerator.h"

Board::Board(BoardCell ***cells) {
    this->coloniesCells = new list<ColonyCell *>;
    this->antList = new list<Ant *>;
    this->cells = cells;
    this->antQueen = nullptr;

    m_tileset.loadFromFile("./assets/tileset.png");
}

Board::~Board() {
    delete antQueen;

    for (Ant *ant: *antList) {
        delete ant;
    }
    delete antList;

    for (int height = 0; height < Config::get()->getHeight(); height++) {
        for (int length = 0; length < Config::get()->getLength(); length++) {
            delete cells[height][length];
        }
        delete cells[height];
    }

    delete cells;
    delete coloniesCells;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(floor_vertex, states);
    target.draw(layer_vertex, states);
}


bool Board::calcRender() {
    int maxLength = Config::get()->getLength();
    int maxHeight = Config::get()->getHeight();
    sf::Vector2u tileSize = sf::Vector2u(Config::get()->getTileSize(), Config::get()->getTileSize());

    int floorVerticeSize = maxLength * maxHeight * 4;
    int layerVertriceSize = 0;

    // create new vertex array
    sf::VertexArray tmpFloorVertex(sf::Quads, floorVerticeSize);
    sf::VertexArray tmpLayerVertex(sf::Quads, layerVertriceSize);



    for (int height = 0; height < maxHeight; ++height) {
        for (int length = 0; length < maxLength; ++length) {
            // Cells with multiple layers
            BoardCell *cell = cells[height][length];


            list<int> cellLayers = cell->getLayersTileNumbers();
            for (auto const &tileNumber: cellLayers){
                layerVertriceSize += 4;
                tmpLayerVertex.resize(layerVertriceSize);

                sf::Vertex *layerQuad = &tmpLayerVertex[layerVertriceSize - 4];

                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // define its 4 corners
                layerQuad[0].position = sf::Vector2f(length * tileSize.x, height * tileSize.y);
                layerQuad[1].position = sf::Vector2f((length + 1) * tileSize.x, height * tileSize.y);
                layerQuad[2].position = sf::Vector2f((length + 1) * tileSize.x, (height + 1) * tileSize.y);
                layerQuad[3].position = sf::Vector2f(length * tileSize.x, (height + 1) * tileSize.y);

                // define its 4 texture coordinates
                layerQuad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                layerQuad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                layerQuad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                layerQuad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

            // get the current tile number
            int tileNumber = cell->getFloorTileNumber();

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex *quad = &tmpFloorVertex[(length + (height * maxLength)) * 4];

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

    floor_vertex = tmpFloorVertex;
    layer_vertex = tmpLayerVertex;
    return true;
}

list<BoardCell *> Board::getNearbyCells(BoardCell *cell) {
    return getNearbyCells(cell->getPosHeight(), cell->getPosLength());
}

list<BoardCell *> Board::getNearbyCells(int height, int length) {
    list<BoardCell *> nearbyCells;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int tmpHeight = height + i;
            int tmpLength = length + j;
            if (tmpHeight < 0 || tmpLength < 0 || tmpHeight >= Config::get()->getHeight() ||
                tmpLength >= Config::get()->getLength()) {
                continue;
            }

            if (this->cells[tmpHeight][tmpLength] != nullptr) {
                nearbyCells.push_back(this->cells[tmpHeight][tmpLength]);
            }
        }
    }

    return nearbyCells;
}

BoardCell *Board::getCenterCell() {
    return cells[Config::get()->getHeight() / 2][Config::get()->getLength() / 2];
}

void Board::expandColonies() {
    BasicCell *expCell = findExpandableBasicCell();
    if (expCell == nullptr) {
        cerr << "Impossible to expand the colony" << endl;
        return;
    }

    auto antOnCell = *expCell->getAntOnCell();
    int length = expCell->getPosLength();
    int height = expCell->getPosHeight();

    expCell->~BasicCell();

    auto *newColonyCell = new(expCell) ColonyCell(height, length);

    for (Ant *ant: antOnCell) {
        newColonyCell->addAntOnCell(ant);
    }

    addColoniesCell(newColonyCell);
}

BasicCell *Board::findExpandableBasicCell() {
    BasicCell *expandCellFound = nullptr;

    for (ColonyCell *colonyCell: *getColoniesCells()) {
        auto nearbyCells = getNearbyCells(colonyCell);

        for (BoardCell *nearbyCell: nearbyCells) {
            if ((nearbyCell->getPosHeight() != colonyCell->getPosHeight() && // No generation in the diagonal
                 nearbyCell->getPosLength() != colonyCell->getPosLength())
                || nearbyCell->getBoardCellType() != BasicCellType) {
                continue;
            }

            expandCellFound = dynamic_cast<BasicCell *>(nearbyCell);
            break;
        }

        if (expandCellFound != nullptr) {
            return expandCellFound;
        }
    }

    return nullptr;
}