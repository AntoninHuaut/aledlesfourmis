#include <iostream>
#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/map/BoardGenerator.h"
#include "../header/core/GUIMain.h"
#include "../header/core/Game.h"

using namespace std;

void gameTickingThread(Board *board) {
    sf::Clock clock;
    Game *game = new Game(board);

    float wantedTPS = Config::get()->getMaxTps();
    auto minDiffMicroSecond = static_cast<sf::Int64>((1.f / wantedTPS) * pow(10, 6));

    while (!board->isWindowClosed() && board->isQueenAlive()) {
        clock.restart();
        game->tickGame();
        sf::Time elapsed = clock.getElapsedTime();

        sf::Int64 diffMicroSecond = elapsed.asMicroseconds();
        sf::Int64 sleepTime = minDiffMicroSecond - diffMicroSecond;

        if (sleepTime > 0) {
            sf::sleep(sf::microseconds(sleepTime));
        }
    }
}

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    Config::get(); // Force configuration to be loaded

    auto *board = BoardGenerator::generateBoard();

    sf::Thread thread(&gameTickingThread, board);
    thread.launch();

    new GUIMain(board);

    return 0;
}
