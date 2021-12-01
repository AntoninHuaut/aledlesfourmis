#include "../../header/core/Game.h"
#include "../../header/ant/Queen.h"

void Game::tickGame() {
    tickQueen();
    tickAnts();

    board->incrementCurrentTick();
}

void Game::tickAnts() {
    list<Ant *> antDeleteList{};
    for (auto *ant: *board->getAntList()) {
        if (ant == nullptr) continue; // Should never happen
        if (!ant->isAlive()) {
            antDeleteList.push_back(ant);
            continue;
        }

        ant->tick(board);
    }

    for (auto *antToDelete: antDeleteList) {
        board->getAntList()->remove(antToDelete);
        delete antToDelete;
    }
}

void Game::tickQueen() {
    Queen *queen = board->getAntQueen();
    if (queen == nullptr) return;

    if (!queen->isAlive()) {
        cerr << "Queen DIE" << endl;
        board->setAntQueen(nullptr);
        delete queen;
        // TODO END GAME
        return;
    }

    queen->tick(board);
}