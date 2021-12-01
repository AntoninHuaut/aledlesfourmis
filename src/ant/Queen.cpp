#include "../../header/ant/Queen.h"
#include "../../header/map/BoardCell.h"
#include "../../header/map/Board.h"
#include "../../header/ant/Scout.h"
#include "../../header/ant/Worker.h"
#include "../../header/ant/Soldier.h"

void Queen::tick(Board *board) {
    Ant::tick(board);

    tickChild(board);
}

void Queen::tickChild(Board *board) {
    if (board->getCurrentTick() % 24 != 0) return;

    if (this->isAssaulted()) {
        this->setAssaulted(false);
        return;
    }

    for (int i = 0; i < 2; i++) {
        generateAnt(board);
    }

    // TODO CREATE NEW COLONY IF COLONIESCELL * 100 > ACTUAL NB ANT
}

void Queen::generateAnt(Board *board) {
    BoardCell *spawnCell = board->getCenterCell();

    Ant *ant = nbChild > 0 ? createRandomAnt(spawnCell) : new Scout(spawnCell);
    board->getAntList()->push_back(ant);
}

Ant *Queen::createRandomAnt(BoardCell *spawnCell) {
    nbChild++;

    int luck = CustomRandom::randInt(1, 100);
    if (luck <= 80) {
        return new Worker(spawnCell);
    } else if (luck <= 95) {
        return new Soldier(spawnCell);
    } else {
        return new Scout(spawnCell);
    }
}
