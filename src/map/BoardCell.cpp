#include "../../header/map/BoardCell.h"
#include "../../header/ant/Ant.h"

BoardCell::BoardCell(int posLength, int posHeight, int maxAntOnCell, BoardCellType boardCellType) {
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
        layers ++;
    }

    if(!this->visited){
        layers ++;
    }

    return layers;
}

list<int> *BoardCell::getBottomLayerTileNumbers() {
    auto *tiles = new list<int>;

    if (!antOnCell->empty()) {
        tiles->push_back(antOnCell->back()->getAntTileNumber());
    }

    return tiles;
}

list<int> *BoardCell::getTopLayerTileNumbers() {
    auto *tiles = new list<int>;

    if (!visited) {
        tiles->push_back(CLOUD_LAYER);
    }

    return tiles;
}

list<int> *BoardCell::getOtherLayerTileNumbers() {

    auto *tiles = getBottomLayerTileNumbers();
    auto *top = getTopLayerTileNumbers();

    tiles->splice(tiles->end(),*top);

    free(top);
    return tiles;
}
