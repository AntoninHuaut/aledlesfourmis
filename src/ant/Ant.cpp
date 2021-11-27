#include "../../header/ant/Ant.h"

int Ant::getAntTileNumber() {
    int tile = BLACK_ANT;

    if (!cellTraveledSinceColony->empty()) {

        BoardCell *lastCell = cellTraveledSinceColony->back();
        int lengthDiff = currentCell->getPosLength() - lastCell->getPosLength();
        int heightDiff = currentCell->getPosHeight() - lastCell->getPosHeight();

        if (lengthDiff == 1 && heightDiff == 0)
            tile += 1;
        else if (lengthDiff == 1 && heightDiff == 1)
            tile += 2;
        else if (lengthDiff == 0 && heightDiff == 1)
            tile += 3;
        else if (lengthDiff == -1 && heightDiff == 1)
            tile += 4;
        else if (lengthDiff == -1 && heightDiff == 0)
            tile += 5;
        else if (lengthDiff == -1 && heightDiff == -1)
            tile += 6;
        else if (lengthDiff == 0 && heightDiff == -1)
            tile += 7;

    }
    
    return tile;
}
