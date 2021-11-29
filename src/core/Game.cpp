#include "../../header/core/Game.h"
#include "../../header/ant/Ant.h"
#include "../../header/ant/Queen.h"

void Game::tickGame() {
    tickQueen();
    tickAnts();

    board->calcRender();
}

void Game::tickAnts() {
    for (auto *ant: *board->getAntList()) {
        // TODO arg
        // increment age
        // move ant
        // consume food
        ant->tick(board);
    }
}

void Game::tickQueen() {
    board->getAntQueen()->tick(board);
}
