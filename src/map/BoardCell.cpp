#include "../../header/map/BoardCell.h"


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
    if (!this->antOnCell->empty()) {
        return 2;
    }

    return 1;
}

list<int> *BoardCell::getOtherLayerTileNumbers() {
    auto *tiles = new list<int>;

    if (!antOnCell->empty()) {
        tiles->push_back(antOnCell->back()->getAntTileNumber());
    }

    return tiles;
}

list<Ant *> *BoardCell::getAntOnCell() const {
    return antOnCell;
}

void BoardCell::addAntOnCell(Ant *antToAdd) {
    this->antOnCell->push_back(antToAdd);
}

void BoardCell::removeAntOnCell(Ant *antToRemove) {
    this->antOnCell->remove(antToRemove);
}
