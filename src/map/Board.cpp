#include "../../header/map/Board.h"
#include "../../header/map/BoardGenerator.h"
#include "../../header/ant/SlaveOwner.h"

Board::Board(BoardCell ***cells) {
    this->coloniesCells = new list<ColonyCell *>;
    this->antList = new list<Ant *>;
    this->cells = cells;
    this->antQueen = nullptr;

    setRemainingTickBeforeSlaveOwnerSpawn();
    m_tileSet.loadFromFile("./assets/tileset.png");
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

void Board::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileSet;
    target.draw(floor_vertex, states);
    target.draw(layer_vertex, states);
}


bool Board::calcLayer() {
    int maxLength = Config::get()->getLength();
    int maxHeight = Config::get()->getHeight();
    auto tileSize = Vector2i(Config::get()->getTileSize(), Config::get()->getTileSize());

    int layerVerticeSize = 0;

    // create new vertex array
    VertexArray tmpLayerVertex(Quads, layerVerticeSize);

    for (int height = 0; height < maxHeight; ++height) {
        for (int length = 0; length < maxLength; ++length) {
            BoardCell *cell = cells[height][length];

            list<int> cellLayers = cell->getLayersTileNumbers();
            for (auto tileNumber: cellLayers) {
                layerVerticeSize += 4;
                tmpLayerVertex.resize(layerVerticeSize);

                Vertex *layerQuad = &tmpLayerVertex[layerVerticeSize - 4];

                int tu = (int) (tileNumber % (m_tileSet.getSize().x / tileSize.x));
                int tv = (int) (tileNumber / (m_tileSet.getSize().x / tileSize.x));

                // define its 4 corners
                layerQuad[0].position = Vector2f(Vector2i(length * tileSize.x, height * tileSize.y));
                layerQuad[1].position = Vector2f(Vector2i((length + 1) * tileSize.x, height * tileSize.y));
                layerQuad[2].position = Vector2f(Vector2i((length + 1) * tileSize.x, (height + 1) * tileSize.y));
                layerQuad[3].position = Vector2f(Vector2i(length * tileSize.x, (height + 1) * tileSize.y));

                // define its 4 texture coordinates
                layerQuad[0].texCoords = Vector2f(Vector2i(tu * tileSize.x, tv * tileSize.y));
                layerQuad[1].texCoords = Vector2f(Vector2i((tu + 1) * tileSize.x, tv * tileSize.y));
                layerQuad[2].texCoords = Vector2f(Vector2i((tu + 1) * tileSize.x, (tv + 1) * tileSize.y));
                layerQuad[3].texCoords = Vector2f(Vector2i(tu * tileSize.x, (tv + 1) * tileSize.y));
            }

        }
    }

    layer_vertex = tmpLayerVertex;
    return true;
}

bool Board::calcFloor() {
    int maxLength = Config::get()->getLength();
    int maxHeight = Config::get()->getHeight();
    auto tileSize = Vector2i(Config::get()->getTileSize(), Config::get()->getTileSize());

    int floorVerticeSize = maxLength * maxHeight * 4;

    // create new vertex array
    VertexArray tmpFloorVertex(Quads, floorVerticeSize);

    for (int height = 0; height < maxHeight; ++height) {
        for (int length = 0; length < maxLength; ++length) {
            // Cells with multiple layers
            BoardCell *cell = cells[height][length];

            // get the current tile number
            int tileNumber = cell->getFloorTileNumber();

            // find its position in the tileset texture
            int tu = (int) (tileNumber % (m_tileSet.getSize().x / tileSize.x));
            int tv = (int) (tileNumber / (m_tileSet.getSize().x / tileSize.x));

            // get a pointer to the current tile's quad
            Vertex *quad = &tmpFloorVertex[(length + (height * maxLength)) * 4];

            // define its 4 corners
            quad[0].position = Vector2f(Vector2i(length * tileSize.x, height * tileSize.y));
            quad[1].position = Vector2f(Vector2i((length + 1) * tileSize.x, height * tileSize.y));
            quad[2].position = Vector2f(Vector2i((length + 1) * tileSize.x, (height + 1) * tileSize.y));
            quad[3].position = Vector2f(Vector2i(length * tileSize.x, (height + 1) * tileSize.y));

            // define its 4 texture coordinates
            quad[0].texCoords = Vector2f(Vector2i(tu * tileSize.x, tv * tileSize.y));
            quad[1].texCoords = Vector2f(Vector2i((tu + 1) * tileSize.x, tv * tileSize.y));
            quad[2].texCoords = Vector2f(Vector2i((tu + 1) * tileSize.x, (tv + 1) * tileSize.y));
            quad[3].texCoords = Vector2f(Vector2i(tu * tileSize.x, (tv + 1) * tileSize.y));
        }
    }

    floor_vertex = tmpFloorVertex;
    return true;
}


int Board::catchLarva(int nbToCatch) const {
    if (nbToCatch <= 0) return 0;

    int nbKilled = 0;
    for (auto *ant: *getAntList()) {
        if (!ant->isAlive()) continue;

        if (auto *antAge = dynamic_cast<AgeAdult *>(ant)) {
            if (!antAge->isAdult()) {
                nbKilled++;
                ant->kill();
            }

            if (nbKilled >= nbToCatch) {
                break;
            }
        }
    }

    return nbKilled;
}

list<BoardCell *> Board::getNearbyCells(int height, int length) {
    list<BoardCell *> nearbyCells;

    if (!BoardGenerator::isValidCell(height, length)) return nearbyCells;

    return *this->cells[height][length]->getNeighborCells();
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

    auto *newColonyCell = new(expCell) ColonyCell(this, height, length);

    for (Ant *ant: antOnCell) {
        newColonyCell->addAntOnCell(ant);
    }

    addColoniesCell(newColonyCell);
}

BasicCell *Board::findExpandableBasicCell() {
    BasicCell *expandCellFound = nullptr;

    for (ColonyCell *colonyCell: *getColoniesCells()) {
        auto nearbyCells = getNearbyCells(colonyCell->getPosHeight(), colonyCell->getPosLength());

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

void Board::tick() {
    currentTick++;

    remainingTickBeforeSlaveOwnerSpawn--;
    if (remainingTickBeforeSlaveOwnerSpawn <= 0) {
        setRemainingTickBeforeSlaveOwnerSpawn();
        createSlaveOwner();
    }

    for (int height = 0; height < Config::get()->getHeight(); height++) {
        for (int length = 0; length < Config::get()->getLength(); length++) {
            auto *cell = cells[height][length];
            if (cell->getPheromone() <= 0) continue;

            float pheromoneEvaporated = cell->getPheromone() * Config::get()->getPheromoneEvaporationPercent();
            cell->removePheromone(pheromoneEvaporated);

            float pheromoneSpread = cell->getPheromone() * Config::get()->getPheromoneSpreadPercent();

            for (int padHeight = -1; padHeight <= 1 && cell->haveMinPheromone(pheromoneSpread); padHeight++) {
                for (int padLength = -1; padLength <= 1 && cell->haveMinPheromone(pheromoneSpread); padLength++) {
                    if (padHeight == 0 && padLength == 0) continue;

                    int newHeight = height + padHeight;
                    int newLength = length + padLength;

                    if (!BoardGenerator::isValidCell(newHeight, newLength)) continue;

                    auto *neighbor = cells[height][length];
                    if (neighbor->getBoardCellType() != BasicCellType) continue;

                    if (cell->haveMinPheromone(pheromoneSpread)) {
                        cell->removePheromone(pheromoneSpread);
                        neighbor->addPheromone(pheromoneSpread);
                    }
                }
            }
        }
    }
}

void Board::createSlaveOwner() {
    int posOne = CustomRandom::randInt(1, 4); // 1 = NO, 2 = SO, 3 = NE, 4 = SE

    int searchPosHeight = (posOne % 2) == 1 == 1 ? 0 : Config::get()->getHeight() - 1;
    int searchPosLength = posOne <= 2 ? 0 : Config::get()->getLength() - 1;

    int pad = 1;

    while (pad < ((Config::get()->getLength() + Config::get()->getHeight()) / 4)) {
        for (int padHeight = -pad; padHeight <= pad; padHeight++) {
            for (int padLength = -pad; padLength <= pad; padLength++) {
                if (padHeight == 0 && padLength == 0) continue;

                int posHeight = searchPosHeight + padHeight;
                int posLength = searchPosLength + padLength;

                if (!BoardGenerator::isValidCell(posHeight, posLength)) continue;

                auto *cell = cells[posHeight][posLength];
                if (cell->getBoardCellType() != BasicCellType) continue;

                auto *basicCell = dynamic_cast<BasicCell *>(cell);
                auto *slaveOwner = new SlaveOwner(basicCell);
                basicCell->addAntOnCell(slaveOwner);
                addAntToList(slaveOwner);

                return;
            }
        }

        pad++;
    }
}
