#include "../../include/map/ColonyCell.h"
#include "../../include/ant/Ant.h"

list<int> ColonyCell::getLayersTileNumbers() {
    list<int> tiles;

    tiles.push_back(COLONY_FLOOR);

    for (Ant *ant: *antOnCell) {
        if (ant->getAntType() == QueenType) {
            tiles.push_back(QUEEN);
        }
    }

    return tiles;
}
