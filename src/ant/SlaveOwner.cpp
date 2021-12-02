#include "../../header/ant/SlaveOwner.h"
#include "../../header/map/Board.h"

int cellsDistance(BoardCell *cell1, BoardCell *cell2) {
    return abs(cell1->getPosLength() - cell2->getPosLength()) + abs(cell1->getPosHeight() - cell2->getPosHeight());
}

void SlaveOwner::goToCenter(Board *board) {
    auto possibleCells = this->getAvailableCellToMove(board);

    if (possibleCells.empty()) return;

    BoardCell *target = board->getCenterCell();

    int min = cellsDistance(possibleCells.front(), target);
    int minNumberOfVisite = numberOfTimeOnCell(possibleCells.front());

    BoardCell *bestCell = possibleCells.front();

    for (auto *cell: possibleCells) {
        int newDist = cellsDistance(cell, target);

        if (newDist <= min && numberOfTimeOnCell(cell) <= minNumberOfVisite) {
            min = newDist;
            minNumberOfVisite = numberOfTimeOnCell(cell);
            bestCell = cell;
        }
    }

    if (bestCell == target) {
        haveArrivedToCenter = true;
    }

    this->goToCell(bestCell, false);
}

void SlaveOwner::tickMove(Board *board) {
    if (!haveArrivedToCenter) {
        goToCenter(board);
    } else {
        goBackToLastCell();
    }
}

bool SlaveOwner::eatFood(float amountToEat) {
    // TODO on verra plus tard
    return true;
}
