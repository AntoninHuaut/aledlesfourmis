#ifndef ANT_QUEEN_H
#define ANT_QUEEN_H

#include "Ant.h"
#include "../Config.h"

class Queen : public Ant {

    int nbChild = 0;
    bool assaulted = false;

public:
    explicit Queen(BoardCell *currentCell) :
            Ant(Config::get()->getQueenHoursBeforeDeath(), 1, Config::get()->getQueenFoodConsumingTick(),
                currentCell, QueenType) {};

    void setAssaulted(bool newAssaulted) {
        assaulted = newAssaulted;
    }

    bool isAssaulted() const { return assaulted; }

    void tick(Board *board) override;

    void tickChild(Board *board);

    void generateAnt(Board *board);

    Ant *createRandomAnt(BoardCell *spawnCell);
};


#endif