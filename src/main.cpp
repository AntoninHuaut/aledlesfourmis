#include "../include/map/BoardCell.h"
#include "../include/map/BasicCell.h"
#include "../include/map/BoardGenerator.h"
#include "../include/core/GUIMain.h"
#include "../include/core/SimulationStats.h"

using namespace std;

struct gameThreadData {
    Board *board;
    Game *game;
    SimulationStats *stats;
} typedef gameThreadData;

void gameTickingThread(gameThreadData data) {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    sf::Clock clock_TPS;
    sf::Clock clock_FPS;

    float wanted_TPS = Config::get()->getMaxTps();
    auto min_FPS = static_cast<float>(Config::get()->getMinFps());

    data.stats->setWantedTps(static_cast<int>(wanted_TPS));

    auto minDiffMicroSecond_TPS = static_cast<sf::Int64>((1.f / wanted_TPS) * pow(10, 6));
    auto minDiffMicroSecond_FPS = static_cast<sf::Int64>((1.f / min_FPS) * pow(10, 6));

    while (!data.board->isWindowClosed() && data.board->isQueenAlive()) {
        if (data.game->isPause()) {
            data.game->logGNUPlot();
            sf::sleep(milliseconds(100));
            continue;
        }

        clock_TPS.restart();

        data.board->getMutex()->lock();
        data.game->tickGame();
        data.board->getMutex()->unlock();

        sf::Int64 diffMicroSecond_TPS = clock_TPS.getElapsedTime().asMicroseconds();
        sf::Int64 sleepTime_TPS = minDiffMicroSecond_TPS - diffMicroSecond_TPS;

        auto tpsTimeValue = static_cast<double>(diffMicroSecond_TPS + (sleepTime_TPS > 0 ? sleepTime_TPS : 0));
        data.stats->setCurrentTps(static_cast<int>(1 / (tpsTimeValue / pow(10, 6))));

        if (sleepTime_TPS > 0) {
            sf::sleep(sf::microseconds(sleepTime_TPS));
            clock_FPS.restart();
        } else if (clock_FPS.getElapsedTime().asMicroseconds() >= minDiffMicroSecond_FPS) {
            sf::sleep(sf::microseconds(1));
            clock_FPS.restart();
        }
    }

    data.stats->setIsGameEnded(true);
    data.game->logGNUPlot();
}

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    Config::get(); // Force configuration to be loaded
    sf::Mutex mutex;

    auto *board = BoardGenerator::generateBoard(&mutex);
    auto *stats = new SimulationStats();
    auto *game = new Game(board, stats);

    // Launching draw thread
    gameThreadData data;
    data.board = board;
    data.game = game;
    data.stats = stats;
    sf::Thread thread(&gameTickingThread, data);
    thread.launch();

    new GUIMain(game, board, stats);

    delete game;
    delete stats;
    delete board;

    return 0;
}
