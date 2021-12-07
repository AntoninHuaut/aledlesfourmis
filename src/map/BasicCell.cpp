#include "../../header/map/BasicCell.h"

list<int> BasicCell::getLayersTileNumbers() {
    list<int> tiles;

    if (getPheromone() > 0) {
        float maxPheromone = Config::get()->getMaxPheromoneOnCell();
        float step = maxPheromone / 5;

        int toAdd = static_cast<int>(getPheromone() / step);
        if (toAdd > 5) toAdd = 5;

        tiles.push_back(FIRST_PHEROMONE_LEVEL + toAdd);
    }

    if (foodAmount > 1000) {
        tiles.push_back(BIG_FOOD_LAYER);
    } else if (foodAmount > 0) {
        tiles.push_back(FOOD_LAYER);
    }

    if (!antOnCell->empty()) {
        tiles.push_back(antOnCell->back()->getAntTileNumber());
    }

    if (!this->visited) {
        tiles.push_back(CLOUD_LAYER);
    }

    return tiles;
}

