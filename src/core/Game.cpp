#include "../../header/core/Game.h"
#include "../../header/ant/Queen.h"

void Game::tickGame() {
    bool showDebug = board->getCurrentTick() % 100 == 0;
    if (showDebug) cout << "Tick " << board->getCurrentTick() << endl;

    sf::Clock start;
    tickQueen();
    if (showDebug) cout << "Ticking queen in " << start.getElapsedTime().asMicroseconds() << " us" << endl;

    start.restart();
    tickAnts();
    if (showDebug) cout << "Ticking ants in " << start.getElapsedTime().asMicroseconds() << " us" << endl;

    start.restart();
    board->tick();
    if (showDebug) cout << "Ticking board in " << start.getElapsedTime().asMicroseconds() << " us" << endl << endl;
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

        switch (ant->getAntType()) {
            case ScoutType:
                soldier++;
                break;
            case SoldierType:
                scout++;
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

        ant->tick(board);
    }

//    cout << "Tick: " << board->getCurrentTick() << "   Soldier: " << soldier << "   SlaveOwner: " << slaveOwner
//         << "   Worker: " << worker << "   Scout: " << scout << endl;

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