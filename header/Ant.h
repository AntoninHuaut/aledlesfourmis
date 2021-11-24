#ifndef ANT_ANT_H
#define ANT_ANT_H

#include <list>

class BoardCell;

class Ant {

    BoardCell* currentCell = nullptr;
    int dayBeforeDeath;
    double foodConsumedEachDay;

    std::list<BoardCell*> cellTraveledSinceColony;

    virtual void eatFood() {};
    virtual void putPheromones() {};
    virtual void kill() {};

public:
    Ant(int dayBeforeDeath, double foodConsumedEachDay) {
        this->dayBeforeDeath = dayBeforeDeath;
        this->foodConsumedEachDay = foodConsumedEachDay;
    };

    virtual void tick() {};
    virtual bool attackAnt(Ant* target) { return false; };

    void setCell(BoardCell* cell) { this->currentCell = cell; };
    BoardCell* getCurrentCell() { return this->currentCell; };
};

#endif