#ifndef ANT_ANT_H
#define ANT_ANT_H

#include <list>

using namespace std;

class BoardCell;

class Ant {

    BoardCell *currentCell;
    int hoursBeforeDeath;
    int hoursSinceLastFeeding = 0;
    double foodConsumedEachDay;

    list<BoardCell *> *cellTraveledSinceColony{};

    virtual void eatFood() {};

    virtual void putPheromones() {};

    virtual void kill() {};

public:
    Ant(int hoursBeforeDeath, double foodConsumedEachDay, BoardCell *currentCell) {
        this->hoursBeforeDeath = hoursBeforeDeath;
        this->foodConsumedEachDay = foodConsumedEachDay;
        this->currentCell = currentCell;
    };

    virtual void tick() {};

    virtual bool attackAnt(Ant *target) { return false; };

    void setCell(BoardCell *cell) { this->currentCell = cell; };

    BoardCell *getCurrentCell() { return this->currentCell; };

};

#endif