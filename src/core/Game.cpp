#include "../../header/core/Game.h"

void Game::tickGame() {
    incrementAge();
    checkQueenChild();
    moveAnts();
    consumeFoods();

    board->calcRender();
}

void Game::incrementAge() {
    
}

void Game::checkQueenChild() {

}

void Game::moveAnts() {

}

void Game::consumeFoods() {

}