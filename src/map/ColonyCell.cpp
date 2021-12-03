#include "../../header/map/ColonyCell.h"

list<int> ColonyCell::getLayersTileNumbers() {
    list<int> tiles;

    tiles.push_front(COLONY_FLOOR);

    return tiles;
}
