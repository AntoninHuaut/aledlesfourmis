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

list<int> *BasicCell::getOtherLayerTileNumbers() {
    list<int> *tiles = BoardCell::getBottomLayerTileNumbers();

    if (foodAmount > 0) {
        tiles->push_back(FOOD_LAYER);
    }

    auto *topTiles = BoardCell::getTopLayerTileNumbers();

    tiles->splice(tiles->end(), *topTiles);

    return tiles;
}

