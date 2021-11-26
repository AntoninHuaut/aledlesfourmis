#ifndef ANT_BOARDCELL_H
#define ANT_BOARDCELL_H

#include <list>
#include "../ant/Ant.h"
#include "../lib/CustomRandom.h"
#include "../gui/TileEnum.h"

using namespace std;

enum BoardCellType {
    BasicCellType, RockCellType, ColonyCellType
};

class BoardCell {

    int randomCellDecoration;

    int posLength;
    int posHeight;
    BoardCellType boardCellType;

    double pheromoneAmount = 0;
    bool visited = false;
    int maxAntOnCell;
    list<Ant *> *antOnCell = new list<Ant *>;

    void pheromoneSpreading() {};

public:
    explicit BoardCell(int posLength, int posHeight, int maxAntOnCell, BoardCellType boardCellType) {
        this->maxAntOnCell = maxAntOnCell;
        this->posLength = posLength;
        this->posHeight = posHeight;
        this->boardCellType = boardCellType;

        this->randomCellDecoration = CustomRandom::getInstance()->randInt(0, 3);
    };

    virtual void tick() {};

    int numberOfLayers();

    int getPosLength() const { return posLength; }

    int getPosHeight() const { return posHeight; }

    int getMaxAntOnCell() const { return maxAntOnCell; }

    BoardCellType getBoardCellType() const { return boardCellType; }

    bool haveSpace() { return this->antOnCell->size() < maxAntOnCell; }

    int getRandomCellDecoration() const { return this->randomCellDecoration; }

    int getFloorTileNumber();

};

#endif
