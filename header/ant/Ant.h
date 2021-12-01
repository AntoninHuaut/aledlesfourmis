#ifndef ANT_ANT_H
#define ANT_ANT_H

#include <list>
#include <SFML/Graphics.hpp>
#include "../core/TileEnum.h"

using namespace std;

class BoardCell;

class Board;

enum AntType {
    QueenType, ScoutType, SoldierType, WorkerType, SlaveOwnerType
};

class Ant {

    BoardCell *currentCell;
    AntType antType;

    int hoursBeforeDeath;
    int hoursSinceLastFeeding = 0;
    int maxHoursWithoutFeeding;

    virtual bool hasEatFood(double amountToEat);

    bool isDyingHunger() const;

    void genericEatFood();

    virtual void putPheromones() {};


protected:
    list<BoardCell *> *cellTraveledSinceColony = new list<BoardCell *>;

    double foodConsumedEachDay;

    virtual void kill() {};

    static double colonyFood;

public:
    Ant(int hoursBeforeDeath, int maxDaysWithoutFeeding, double foodConsumedEachDay, BoardCell *currentCell,
        AntType antType);

    ~Ant();

    virtual void tick(Board *board) {};

    virtual bool attackAnt(Ant *target) { return false; }

    BoardCell *getCurrentCell() { return this->currentCell; }

    void addCellTraveled(BoardCell *cell) {
        this->cellTraveledSinceColony->push_back(cell);
    }

    int getAntTileNumber();

    AntType getAntType() {
        return antType;
    }

    list<BoardCell *> *getAvailableCellToMove(Board *board);

    void goToCell(BoardCell *newCell);

    bool goBackToLastCell();


};

#endif