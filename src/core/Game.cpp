#include "../../header/core/Game.h"
#include "../../header/ant/Ant.h"
#include "../../header/ant/Queen.h"

void Game::tickGame() {
    tickQueen();
    tickAnts();
    
    board->incrementCurrentTick();
    board->calcRender();
}

void Game::tickAnts() {
    for (auto *ant: *board->getAntList()) {
        ant->tick(board);
    }
}

void Game::tickQueen() {
    Queen *queen = board->getAntQueen();
    if (queen == nullptr) return;

    if (checkAndRemoveDeadAnt(queen)) {
        board->setAntQueen(nullptr);
        // TODO END GAME
        return;
    }

    queen->tick(board);
}

bool Game::checkAndRemoveDeadAnt(Ant *ant) {
    if (!ant->isAlive()) {
        board->getAntList()->remove(ant);
        delete ant;
        return true;
    }

    return false;
}