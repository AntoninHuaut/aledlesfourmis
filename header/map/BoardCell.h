#ifndef ANT_BOARDCELL_H
#define ANT_BOARDCELL_H

#include <list>
#include "../ant/Ant.h"

using namespace std;

enum BoardCellType {
    BasicCellType, RockCellType, ColonyCellType
};

class BoardCell {

    int posLength;
    int posHeight;
    BoardCellType boardCellType;

    double pheromoneAmount = 0;
    bool visited = false;
    int maxAntOnCell;
    list<Ant *> *antOnCell{};

    void pheromoneSpreading() {};

public:
    explicit BoardCell(int posLength, int posHeight, int maxAntOnCell, BoardCellType boardCellType) {
        this->maxAntOnCell = maxAntOnCell;
        this->posLength = posLength;
        this->posHeight = posHeight;
        this->boardCellType = boardCellType;
    };

    virtual void tick() {};

    int getPosLength() const { return posLength; }

    int getPosHeight() const { return posHeight; }

    int getMaxAntOnCell() const { return maxAntOnCell; };

    BoardCellType getBoardCellType() const { return boardCellType; }

    bool haveSpace() { return this->antOnCell->size() < maxAntOnCell; };


};

#endif
