#include "../../header/map/BasicCell.h"

void BasicCell::takeFood(Ant *ant) {

}

int BasicCell::numberOfLayers() {
    int layers = BoardCell::numberOfLayers();

    if (foodAmount > 0) {
        layers++;
    }

    return layers;
}

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

