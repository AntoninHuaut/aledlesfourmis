#include "../../header/map/RockCell.h"

void RockCell::addAntOnCell(Ant *antToAdd) {
    cerr << "RockCell::addAntOnCell FORBIDDEN" << endl;
}

void RockCell::removeAntOnCell(Ant *antToRemove) {
    cerr << "RockCell::removeAntOnCell FORBIDDEN" << endl;
}

void RockCell::onNearCellVisited() {

    visited = true;

}
