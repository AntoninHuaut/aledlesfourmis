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
    if (board->getCurrentTick() % 24 != 0) return; // Only once a day

    // No child if the Queen was assaulted
    if (this->isAssaulted()) {
        this->setAssaulted(false);
        return;
    }

    // Generating two ants
    for (int i = 0; i < Config::get()->getNewAntEveryDay(); i++) {
        generateAnt(board);
    }

    int nbColonies = static_cast<int>(board->getColoniesCells()->size());
    int actualMaxAntsCapacity = Config::get()->getColonyMaxAntOnCell() * nbColonies;

    int nbSlaveOwner = 0;
    for (auto *checkAnt: *board->getAntList()) {
        if (checkAnt->getAntType() != SlaveOwnerType) continue;
        nbSlaveOwner++;
    }
    int nbAnts = static_cast<int>(board->getAntList()->size()) - nbSlaveOwner + 1; // + Queen

    if (nbAnts > actualMaxAntsCapacity) {
        board->expandColonies();
    }
}

void Queen::generateAnt(Board *board) {
    BoardCell *spawnCell = board->getCenterCell();

    Ant *ant = nbChild > 0 ? createRandomAnt(spawnCell) : new Scout(spawnCell);
    board->getAntList()->push_back(ant);

    nbChild++;
}

Ant *Queen::createRandomAnt(BoardCell *spawnCell) {
    int luck = CustomRandom::randInt(1, 100);
    if (luck <= 80) {
        return new Worker(spawnCell);
    } else if (luck <= 95) {
        return new Soldier(spawnCell);
    } else {
        return new Scout(spawnCell);
    }
}