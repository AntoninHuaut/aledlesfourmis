#include "../../include/ant/Scout.h"
#include "../../include/map/Board.h"


void Scout::tickMove(Board *board) {
    auto cells = getAvailableCellToMove(board);
    if (cells.empty()) return;

    list<BoardCell *> unknownCells;

    for (auto const &cell: cells) {
        if (!cell->isVisited()) {
            unknownCells.push_back(cell);
        }
    }

    list<BoardCell *> list = unknownCells.empty() ? cells : unknownCells;

    auto l_front = list.begin();
    std::advance(l_front, CustomRandom::randInt(0, static_cast<int>(list.size()) - 1));

    goToCell(*l_front);
}
