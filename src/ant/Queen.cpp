#include "../../header/ant/Queen.h"
#include "../../header/map/BoardCell.h"
#include "../../header/map/Board.h"

void Queen::tick(Board *board) {
    Ant::tick(board);

    /* TODO TEST : to delete */
    auto *list = getAvailableCellToMove(board);
    if (list->empty()) return;

    auto newCellIt = list->begin();
    std::advance(newCellIt, rand() % list->size()); // NOLINT(cert-msc50-cpp)
    this->goToCell(*newCellIt);
    /* */
}