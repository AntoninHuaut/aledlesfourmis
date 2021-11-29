#include "../../header/ant/Queen.h"
#include "../../header/map/BoardCell.h"

void Queen::tick(Board *board) {
    /* TODO TEST : to delete */
    auto *list = getAvailableCellToMove(board);
    if (list->empty()) return;

    auto *newCell = list->front();
    auto *currentCell = getCurrentCell();

    currentCell->removeAntOnCell(this);
    addCellTraveled(currentCell);

    newCell->addAntOnCell(this);
    setCurrentCell(newCell);
    /* */
}