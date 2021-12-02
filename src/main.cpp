#include <iostream>
#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/map/BoardGenerator.h"
#include "../header/core/GUIMain.h"
#include "../header/core/Game.h"

using namespace std;

void gameTickingThread(Board *board) {
    sf::Clock clock_TPS;
    sf::Clock clock_FPS;

    Game *game = new Game(board);

    float wanted_TPS = Config::get()->getMaxTps();
    int wanted_FPS = Config::get()->getMaxFps();

    auto minDiffMicroSecond_TPS = static_cast<sf::Int64>((1.f / wanted_TPS) * pow(10, 6));
    auto minDiffMicroSecond_FPS = static_cast<sf::Int64>((1.f / static_cast<float>(wanted_FPS)) * pow(10, 6));

    while (!board->isWindowClosed() && board->isQueenAlive()) {
        clock_TPS.restart();
        game->tickGame();

        sf::Int64 diffMicroSecond_FPS = clock_FPS.getElapsedTime().asMicroseconds();
        if (diffMicroSecond_FPS > minDiffMicroSecond_FPS) {
            clock_FPS.restart();
            board->calcRender();
        }

        sf::Int64 diffMicroSecond_TPS = clock_TPS.getElapsedTime().asMicroseconds();
        sf::Int64 sleepTime_TPS = minDiffMicroSecond_TPS - diffMicroSecond_TPS;

        if (sleepTime_TPS > 0) {
            sf::sleep(sf::microseconds(sleepTime_TPS));
        }
    }
}

int main() {
//    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    Config::get(); // Force configuration to be loaded

    auto *board = BoardGenerator::generateBoard();

    sf::Thread thread(&gameTickingThread, board);
    thread.launch();

    new GUIMain(board);

    return 0;
}
