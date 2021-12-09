#include "../../header/ant/SlaveOwner.h"
#include "../../header/ant/Queen.h"
#include "../../header/map/Board.h"

void SlaveOwner::attackQueen(Board *board) {
    auto *queen = board->getAntQueen();
    if (queen == nullptr) return; // Queen is dead (it's the last turn of the game)
    if (queen->getCurrentCell() != getCurrentCell()) return;

    if (hoursSinceLastFeeding > 1) {
        if (eatFood(this->foodConsumedEachDay)) {
            hoursSinceLastFeeding = 0;
        }
    }

    if (larvaCarried >= Config::get()->getSlaveOwnerMaxLarvaCanCarried()) return;

    int maxLarvaToCatch = abs(Config::get()->getSlaveOwnerMaxLarvaCanCarried() - larvaCarried);

    int larvaCaught = board->catchLarva(maxLarvaToCatch);
    if (larvaCaught > 0) {
        queen->setAssaulted(true);
        larvaCarried += larvaCaught;
    }
}

void SlaveOwner::tickMove(Board *board) {
    if (!haveArrivedToColony) {
        if (hoursSinceLastFeeding > 2) {
            auto possibleCells = getAvailableCellToMove(board);
            if (possibleCells.empty()) return;

            for (auto cell: possibleCells) {
                if (cell->getBoardCellType() != BasicCellType) continue;
                auto *basicCell = dynamic_cast<BasicCell *>(cell);
                if (basicCell->getFoodAmount() <= this->foodConsumedEachDay) continue;

                goToCell(basicCell);
                if (eatFood(this->foodConsumedEachDay)) {
                    hoursSinceLastFeeding = 0;
                }
                return;
            }
        }

        goToCenter(board);
    } else if (larvaCarried == 0) {
        attackQueen(board);
    } else {
        goBackToLastCell();
    }
}

void SlaveOwner::tick(Board *board) {
    Ant::tick(board);

    if (cellTraveledSinceStart->empty()) {
        kill();
    }
}

bool SlaveOwner::eatFood(float amountToEat) {
    if (getCurrentCell()->getBoardCellType() == ColonyCellType) {
        return Ant::eatFood(amountToEat);
    }

    if (getCurrentCell()->getBoardCellType() == BasicCellType) {
        auto *basicCell = dynamic_cast<BasicCell *>(getCurrentCell());
        if (basicCell->getFoodAmount() >= amountToEat) {
            basicCell->setFoodAmount(basicCell->getFoodAmount() - amountToEat);
            return true;
        }

        return false;
    }

    return false;
}

void SlaveOwner::goToCenter(Board *board) {
    auto possibleCells = this->getAvailableCellToMove(board);

    if (possibleCells.empty()) return;

    BoardCell *target = board->getCenterCell();

    int min = possibleCells.front()->cellsDistance(target);
    int minNumberOfVisit = numberOfTimeOnCell(possibleCells.front());

    BoardCell *bestCell = possibleCells.front();

    for (auto *cell: possibleCells) {
        int newDist = cell->cellsDistance(target);

        if (newDist <= min && numberOfTimeOnCell(cell) <= minNumberOfVisit) {
            min = newDist;
            minNumberOfVisit = numberOfTimeOnCell(cell);
            bestCell = cell;
        }
    }

    if (bestCell->getBoardCellType() == ColonyCellType) {
        haveArrivedToColony = true;
    }

    this->goToCell(bestCell);
}