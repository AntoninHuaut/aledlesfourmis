#include "../../header/ant/Scout.h"
#include "../../header/map/Board.h"

void Scout::tickMove(Board *board) {
    auto cells = getAvailableCellToMove(board);
    if (cells.empty()) return;

    list<BoardCell *> unknownCells;

    for (auto const &cell: cells) {
        if (!cell->isVisited()) {
            unknownCells.push_back(cell);
        }
    }

    BoardCell *nextCell;

    if (!unknownCells.empty()) {
        auto l_front = unknownCells.begin();
        std::advance(l_front, CustomRandom::randInt(0, static_cast<int>(unknownCells.size()) - 1));
        nextCell = *l_front;
    } else {
        auto l_front = cells.begin();
        std::advance(l_front, CustomRandom::randInt(0, static_cast<int>(cells.size()) - 1));
        nextCell = *l_front;
    }

    goToCell(nextCell);
}
