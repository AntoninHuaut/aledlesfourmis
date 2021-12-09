#include "../../header/map/BoardCell.h"
#include "../../header/map/Board.h"

BoardCell::BoardCell(Board *board, int posHeight, int posLength, int maxAntOnCell, BoardCellType boardCellType) {
    this->board = board;
    this->posHeight = posHeight;
    this->posLength = posLength;
    this->maxAntOnCell = maxAntOnCell;
    this->boardCellType = boardCellType;

    this->randomCellDecoration = CustomRandom::randInt(0, 3);
}

BoardCell::~BoardCell() {
    delete antOnCell;
    delete neighborCells;
}

int BoardCell::getFloorTileNumber() {

    switch (this->boardCellType) {
        case ColonyCellType:
            return COLONY_FLOOR;

        case RockCellType:
            return ROCK_FLOOR;

        default:
            return BASIC_FLOOR + (this->getRandomCellDecoration());
    }
}

list<int> BoardCell::getLayersTileNumbers() {
    list<int> tiles;

    if (!antOnCell->empty()) {
        tiles.push_back(antOnCell->back()->getAntTileNumber());
    }

    if (!this->visited) {
        tiles.push_back(CLOUD_LAYER);
    }

    return tiles;
}

void BoardCell::addAntOnCell(Ant *antToAdd) {
    this->antOnCell->push_back(antToAdd);

    if (!this->visited && antToAdd->getAntType() != SlaveOwnerType) {
        this->visited = true;

        list<BoardCell *> nearbyCells = board->getNearbyCells(this->getPosHeight(), this->getPosLength());
        for (auto *cell: nearbyCells) {
            cell->onNearCellVisited();
        }
    }

}

void BoardCell::removeAntOnCell(Ant *antToRemove) {
    this->antOnCell->remove(antToRemove);
}

int BoardCell::cellsDistance(BoardCell *cell2) const {
    return abs(getPosLength() - cell2->getPosLength()) + abs(getPosHeight() - cell2->getPosHeight());
}

list<BoardCell *> *BoardCell::getNeighborCells() const {
    if (neighborCells->empty()) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;

                int tmpHeight = getPosHeight() + i;
                int tmpLength = getPosLength() + j;
                if (tmpHeight < 0 || tmpLength < 0 || tmpHeight >= Config::get()->getHeight() ||
                    tmpLength >= Config::get()->getLength()) {
                    continue;
                }

                if (board->getCells()[tmpHeight][tmpLength] != nullptr) {
                    neighborCells->push_back(board->getCells()[tmpHeight][tmpLength]);
                }
            }
        }
    }

    return neighborCells;
}

float BoardCell::addPheromone(float amount) {
    pheromoneAmount += amount;
    float excess = pheromoneAmount - Config::get()->getMaxPheromoneOnCell();
    excess = max(excess, 0.f);
    pheromoneAmount -= excess;
    return amount - excess;
}

void BoardCell::removePheromone(float amount) {
    pheromoneAmount -= amount;
    if (pheromoneAmount < 0.01) {
        pheromoneAmount = 0;
    }
}

bool BoardCell::haveMinPheromone(float amount) const {
    return pheromoneAmount >= amount;
}
