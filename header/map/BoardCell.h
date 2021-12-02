#ifndef ANT_BOARDCELL_H
#define ANT_BOARDCELL_H

#include <list>
#include "../lib/CustomRandom.h"
#include "../core/TileEnum.h"

using namespace std;

class Ant;

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
    explicit BoardCell(int posLength, int posHeight, int maxAntOnCell, BoardCellType boardCellType);

    ~BoardCell();

    virtual void tick() {};

    virtual int numberOfLayers();

    int getPosLength() const { return posLength; }

    int getPosHeight() const { return posHeight; }

    int getMaxAntOnCell() const { return maxAntOnCell; }

    BoardCellType getBoardCellType() const { return boardCellType; }

    bool haveSpace() { return this->antOnCell->size() < maxAntOnCell; }

    int getRandomCellDecoration() const { return this->randomCellDecoration; }

    int getFloorTileNumber();

    virtual list<int> getBottomLayerTileNumbers();

    list<int> getTopLayerTileNumbers();

    virtual list<int> getOtherLayerTileNumbers();

    list<Ant *> *getAntOnCell() const {
        return antOnCell;
    }

    void addAntOnCell(Ant *antToAdd) {
        this->antOnCell->push_back(antToAdd);
    }

    void removeAntOnCell(Ant *antToRemove) {
        this->antOnCell->remove(antToRemove);
    }

    void setVisited(bool isVisited) {
        this->visited = isVisited;
    }

    bool isVisited() const {
        return this->visited;
    }

};

#endif
