#include "../../header/core/Game.h"
#include "../../header/ant/Queen.h"

void Game::tickGame() {
    sf::Clock start;
    bool showDebug = Config::get()->isDev() && board->getCurrentTick() % 500 == 0;
    if (showDebug) cout << "Tick " << board->getCurrentTick() << endl;

    start.restart();
    tickQueen();
    if (showDebug) cout << "Ticking queen in " << start.getElapsedTime().asMicroseconds() << " us" << endl;

    start.restart();
    tickAnts();
    if (showDebug) cout << "Ticking ants in " << start.getElapsedTime().asMicroseconds() << " us" << endl;

    start.restart();
    board->tick();
    if (showDebug) cout << "Ticking board in " << start.getElapsedTime().asMicroseconds() << " us" << endl << endl;

    saveCurrentTick();
}

void Game::tickAnts() {
    list<Ant *> antDeleteList{};

    int soldier = 0;
    int slaveOwner = 0;
    int worker = 0;
    int scout = 0;

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

void Game::saveCurrentTick() {
    string tick = "\n";

    int soldier = 0;
    int slaveOwner = 0;
    int worker = 0;
    int scout = 0;

    for (auto *ant: *board->getAntList()) {
        switch (ant->getAntType()) {
            case ScoutType:
                scout++;
                break;
            case SoldierType:
                soldier++;
                break;
            case WorkerType:
                worker++;
                break;
            case SlaveOwnerType:
                slaveOwner++;
                break;
            default:
                break;
        }
    }

    int intValues[] = {board->getCurrentTick(), soldier + slaveOwner + worker + scout + 1, soldier, // +1 for queen
                       slaveOwner, worker, scout};
    for (int value: intValues) {
        tick.append(to_string(value));
        tick.append(" ");
    }

    float floatValues[] = {Ant::getColonyFood()};
    for (float value: floatValues) {
        tick.append(to_string(value));
        tick.append(" ");
    }

    bufferGNUPlot.append(tick);
}

void Game::logGNUPlot() {
    if (bufferGNUPlot.empty()) return;

    ofstream outfile;

    outfile.open(gnuPlotFile, ios_base::app);
    outfile << bufferGNUPlot;
    outfile.close();

    bufferGNUPlot.clear();
}

bool Game::isPause() const {
    return pause;
}

void Game::setPause(bool newPause) {
    Game::pause = newPause;
}
