#ifndef ANT_BOARDGENERATOR_H
#define ANT_BOARDGENERATOR_H

#include <cstdlib>
#include <stdexcept>
#include <cmath>

#include "Board.h"
#include "BoardCell.h"
#include "BasicCell.h"
#include "RockCell.h"
#include "ColonyCell.h"
#include "../Config.h"

using namespace std;

class BoardGenerator {

    Board *board;

    static BoardGenerator *createBoard();

    void generateSmallFoodUnit();

    void generateBigFoodUnit();

    void generateBigFoodUnitCross(int heightCenter, int searchPosLength);

    BasicCell *findCellNearCoordinateWithCrossCellFree(int height, int length);

    bool isBasicCellsCrossEmpty(int centerHeight, int centerLength);

    bool isValidBigFoodUnitCell(int height, int length);

    void generateRock();

    void generateBasicCell();

    bool hasRockNeighbor(int height, int length);

    bool hasFoodNeighbor(int height, int length);

    static bool isValidCell(int height, int length);

    static int randInt(int maxInclusive, int minInclusive);

public:
    explicit BoardGenerator(Board *board) {
        this->board = board;
    }

    Board *getBoard() { return board; }

    static Board *generateBoard();
};

#endif
