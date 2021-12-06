#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/map/BoardGenerator.h"
#include "../header/core/GUIMain.h"
#include "../header/core/Game.h"

using namespace std;

struct gameThreadData {
    sf::Mutex *mutex;
    Board *board;
} typedef gameThreadData;

void gameTickingThread(gameThreadData data) {
    sf::Clock clock_TPS;

    Game *game = new Game(data.board);

    float wanted_TPS = Config::get()->getMaxTps();
    auto minDiffMicroSecond_TPS = static_cast<sf::Int64>((1.f / wanted_TPS) * pow(10, 6));

    while (!data.board->isWindowClosed() && data.board->isQueenAlive()) {
        clock_TPS.restart();

        data.mutex->lock();
        game->tickGame();
        data.mutex->unlock();

        sf::Int64 diffMicroSecond_TPS = clock_TPS.getElapsedTime().asMicroseconds();
        sf::Int64 sleepTime_TPS = minDiffMicroSecond_TPS - diffMicroSecond_TPS;

        if (sleepTime_TPS > 0) {
            sf::sleep(sf::microseconds(sleepTime_TPS));
        }
    }
}

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    Config::get(); // Force configuration to be loaded
    sf::Mutex mutex;

    auto *board = BoardGenerator::generateBoard();

    // Launching draw thread
    gameThreadData data;
    data.board = board;
    data.mutex = &mutex;
    sf::Thread thread(&gameTickingThread, data);
    thread.launch();

    new GUIMain(&mutex, board);

    return 0;
}
