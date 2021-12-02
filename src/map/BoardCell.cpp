#include "../../header/map/BoardCell.h"
#include "../../header/ant/Ant.h"

BoardCell::BoardCell(int posHeight, int posLength, int maxAntOnCell, BoardCellType boardCellType) {
    this->maxAntOnCell = maxAntOnCell;
    this->posLength = posLength;
    this->posHeight = posHeight;
    this->boardCellType = boardCellType;

    this->randomCellDecoration = CustomRandom::randInt(0, 3);
};

BoardCell::~BoardCell() {
    delete antOnCell;
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

int BoardCell::numberOfLayers() {
    int layers = 1;

    if (!this->antOnCell->empty()) {
        layers++;
    }

    if (!this->visited) {
        layers++;
    }

    return layers;
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

    if (antToAdd->getAntType() != SlaveOwnerType) {
        this->visited = true;
    }

}

void BoardCell::removeAntOnCell(Ant *antToRemove) {
    this->antOnCell->remove(antToRemove);
}
