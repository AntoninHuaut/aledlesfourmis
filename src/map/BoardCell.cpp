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