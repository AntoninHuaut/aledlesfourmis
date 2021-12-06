#include "../../header/map/BasicCell.h"

list<int> BasicCell::getLayersTileNumbers() {
    list<int> tiles;

    if (!antOnCell->empty()) {
        tiles.push_back(antOnCell->back()->getAntTileNumber());
    }

    if (foodAmount > 0) {
        tiles.push_back(FOOD_LAYER);
    }

    if (!this->visited) {
        tiles.push_back(CLOUD_LAYER);
    }

    return tiles;
}

