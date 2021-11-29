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

    float wantedTPS = 1;
    auto minDiffMicroSecond = static_cast<sf::Int64>((1.f / wantedTPS) * pow(10, 6));

    int test = 0;
    while (!board->isFinishGame()) { // TODO while queen is alive or game stop (window closed)
        clock.restart();
        game->tickGame();
        sf::Time elapsed = clock.getElapsedTime();

        sf::Int64 diffMicroSecond = elapsed.asMicroseconds();
//        auto currentTps = (1.0 / static_cast<float>(diffMicroSecond) * pow(10, 6));
//        cout << "Current TPS: " << currentTps << endl;
//        cout << "Diff microSecond: " << diffMicroSecond << endl;
//        cout << "Min diff second: " << minDiffMicroSecond << endl;

        sf::Int64 sleepTime = minDiffMicroSecond - diffMicroSecond;
//        auto sleepTimeFloat = static_cast<float>(sleepTime);

        if (sleepTime > 0) {
//            cout << "Sleeping: " << (sleepTimeFloat / pow(10, 6))
//                 << " second for getting " << wantedTPS << " tps" << endl;
            sf::sleep(sf::microseconds(sleepTime));
        }

//        cout << endl;

        test++;
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
