#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/map/BoardGenerator.h"
#include "../header/core/GUIMain.h"
#include "../header/core/Game.h"

using namespace std;

struct gameThreadData {
    sf::Mutex *mutex;
    Board *board;
    Game *game;
} typedef gameThreadData;

void gameTickingThread(gameThreadData data) {
    sf::Clock clock_TPS;
    sf::Clock clock_FPS;

    float wanted_TPS = Config::get()->getMaxTps();
    auto min_FPS = static_cast<float>(Config::get()->getMinFps());

    auto minDiffMicroSecond_TPS = static_cast<sf::Int64>((1.f / wanted_TPS) * pow(10, 6));
    auto minDiffMicroSecond_FPS = static_cast<sf::Int64>((1.f / min_FPS) * pow(10, 6));

    while (!data.board->isWindowClosed() && data.board->isQueenAlive()) {
        if (data.game->isPause()) {
            sf::sleep(milliseconds(1));
            continue;
        }

        clock_TPS.restart();

        data.mutex->lock();
        data.game->tickGame();
        data.mutex->unlock();

        sf::Int64 diffMicroSecond_TPS = clock_TPS.getElapsedTime().asMicroseconds();
        sf::Int64 sleepTime_TPS = minDiffMicroSecond_TPS - diffMicroSecond_TPS;

        if (sleepTime_TPS > 0) {
            sf::sleep(sf::microseconds(sleepTime_TPS));
            clock_FPS.restart();
        } else if (clock_FPS.getElapsedTime().asMicroseconds() >= minDiffMicroSecond_FPS) {
            clock_FPS.restart();
            sf::sleep(sf::microseconds(1));
        }
    }

    data.game->logGNUPlot();
}

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    Config::get(); // Force configuration to be loaded
    sf::Mutex mutex;

    auto *board = BoardGenerator::generateBoard();
    auto *game = new Game(board);

    // Launching draw thread
    gameThreadData data;
    data.board = board;
    data.mutex = &mutex;
    data.game = game;
    sf::Thread thread(&gameTickingThread, data);
    thread.launch();

    new GUIMain(&mutex, game, board);

    delete board;
    delete game;

    return 0;
}
