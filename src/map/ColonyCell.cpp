#include "../../header/map/ColonyCell.h"
#include "../../header/ant/Ant.h"

list<int> ColonyCell::getLayersTileNumbers() {
    list<int> tiles;

    tiles.push_back(COLONY_FLOOR);

    for(Ant *ant : *antOnCell){
        if (ant->getAntType() == QueenType){
            tiles.push_back(QUEEN);
        }
    }

    return tiles;
}
