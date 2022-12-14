#ifndef ANT_BOARDCELL_H
#define ANT_BOARDCELL_H

#include <list>
#include <cmath>
#include "../lib/CustomRandom.h"
#include "../core/TileEnum.h"
#include "../Config.h"

using namespace std;

class Board;

class Ant;

class Board;

enum BoardCellType {
    BasicCellType, RockCellType, ColonyCellType
};

class BoardCell {

    int randomCellDecoration;

    int posLength;
    int posHeight;
    BoardCellType boardCellType;

    float pheromoneAmount = 0;
    int maxAntOnCell;

    Board *board;

    list<BoardCell *> *neighborCells = new list<BoardCell *>;

protected:
    list<Ant *> *antOnCell = new list<Ant *>;

    bool visited = false;

    void setVisited(bool isVisited) {
        this->visited = isVisited;
    }

public:
    explicit BoardCell(Board *board, int height, int length, int maxAntOnCell, BoardCellType boardCellType);

    ~BoardCell();

    virtual void tick() {};

    int getPosLength() const { return posLength; }

    int getPosHeight() const { return posHeight; }

    int getMaxAntOnCell() const { return maxAntOnCell; }

    BoardCellType getBoardCellType() const { return boardCellType; }

    bool haveSpace() { return this->antOnCell->size() < maxAntOnCell; }

    int getRandomCellDecoration() const { return this->randomCellDecoration; }

    int getFloorTileNumber();

    virtual list<int> getLayersTileNumbers();

    list<Ant *> *getAntOnCell() const {
        return antOnCell;
    }

    float addPheromone(float amount);

    void removePheromone(float amount);

    bool haveMinPheromone(float amount) const;

    float getPheromone() const { return pheromoneAmount; }

    list<BoardCell *> *getNeighborCells() const;

    virtual void addAntOnCell(Ant *antToAdd);

    virtual void removeAntOnCell(Ant *antToRemove);

    virtual void onNearCellVisited() {};

    int cellsDistance(BoardCell *cell2) const;

    bool isVisited() const {
        return this->visited;
    }

};

#endif
