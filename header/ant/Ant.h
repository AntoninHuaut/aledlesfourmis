#ifndef ANT_ANT_H
#define ANT_ANT_H

#include <list>
#include <SFML/Graphics.hpp>
#include "../gui/TileEnum.h"
#include "../map/BoardCell.h"

using namespace std;

class BoardCell;

enum AntType {
    QueenType, ScoutType, SoldierType, WorkerType, SlaveOwnerType
};

class Ant {

    BoardCell *currentCell;
    AntType antType;

    int hoursBeforeDeath;
    int hoursSinceLastFeeding = 0;
    double foodConsumedEachDay;

    list<BoardCell *> *cellTraveledSinceColony = new list<BoardCell *>;

    virtual void eatFood() {};

    virtual void putPheromones() {};

    virtual void kill() {};

public:
    Ant(int hoursBeforeDeath, double foodConsumedEachDay, BoardCell *currentCell, AntType antType) {
        this->hoursBeforeDeath = hoursBeforeDeath;
        this->foodConsumedEachDay = foodConsumedEachDay;
        this->currentCell = currentCell;
        this->antType = antType;
    };

    virtual void tick() {};

    virtual bool attackAnt(Ant *target) { return false; }

    void setCell(BoardCell *cell) { this->currentCell = cell; }

    BoardCell *getCurrentCell() { return this->currentCell; }

    int getAntTileNumber();

    AntType getAntType() {
        return antType;
    }

};

#endif