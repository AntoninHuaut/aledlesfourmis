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
    BoardCell *lastCell = nullptr;

    AntType antType;

    int hoursBeforeDeath;
    int alive = true;
    int maxHoursWithoutFeeding;

    virtual void tickMove(Board *board) {};

    bool isDyingHunger() const;

    void tickFood(Board *board);

protected:
    list<BoardCell *> *cellTraveledSinceColony = new list<BoardCell *>;

    float foodConsumedEachDay;

    void setAlive(bool newAlive) { alive = newAlive; }

    virtual bool eatFood(float amountToEat);

    static float colonyFood;

    int hoursSinceLastFeeding = 0;
    
public:

    Ant(int hoursBeforeDeath, int maxHoursWithoutFeeding, float foodConsumedEachDay, BoardCell *currentCell,
        AntType antType);

    ~Ant();

    virtual void tick(Board *board);

    virtual void kill();

    virtual bool attackAnt(Ant *target) { return false; }

    BoardCell *getCurrentCell() { return this->currentCell; }

    void setCurrentCell(BoardCell *newCurrentCell) { currentCell = newCurrentCell; }

    void addCellTraveled(BoardCell *cell) {
        this->cellTraveledSinceColony->push_back(cell);
    }

    int getAntTileNumber();

    AntType getAntType() {
        return antType;
    }

    bool isAlive() const { return alive; }

    list<BoardCell *> getAvailableCellToMove(Board *board);

    void goToCell(BoardCell *newCell);

    int numberOfTimeOnCell(BoardCell *cell);

    bool goBackToLastCell();
};

#endif