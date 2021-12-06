#include "../../header/ant/SlaveOwner.h"
#include "../../header/ant/Queen.h"
#include "../../header/map/Board.h"

int cellsDistance(BoardCell *cell1, BoardCell *cell2) {
    return abs(cell1->getPosLength() - cell2->getPosLength()) + abs(cell1->getPosHeight() - cell2->getPosHeight());
}

void SlaveOwner::goToCenter(Board *board) {
    auto possibleCells = this->getAvailableCellToMove(board);

    if (possibleCells.empty()) return;

    BoardCell *target = board->getCenterCell();

    int min = cellsDistance(possibleCells.front(), target);
    int minNumberOfVisit = numberOfTimeOnCell(possibleCells.front());

    BoardCell *bestCell = possibleCells.front();

    for (auto *cell: possibleCells) {
        int newDist = cellsDistance(cell, target);

        if (newDist <= min && numberOfTimeOnCell(cell) <= minNumberOfVisit) {
            min = newDist;
            minNumberOfVisit = numberOfTimeOnCell(cell);
            bestCell = cell;
        }
    }

    if (bestCell == target) {
        haveArrivedToCenter = true;
    }

    this->goToCell(bestCell);
}

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
    if (!haveArrivedToCenter) {
        goToCenter(board);
    } else if (larvaCarried == 0) {
        attackQueen(board);
    } else {
        goBackToLastCell();
    }
}

void SlaveOwner::tick(Board *board) {
    Ant::tick(board);

    if (cellTraveledSinceColony->empty()) {
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
