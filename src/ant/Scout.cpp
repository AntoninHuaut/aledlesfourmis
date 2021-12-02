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
        int randCell = CustomRandom::randInt(0, static_cast<int>(unknownCells.size()) - 1);
        int i = 0;
        for (auto *cell: unknownCells) {
            nextCell = cell;
            if (i == randCell) {
                break;
            }
            i++;
        }
    } else {
        int randCell = CustomRandom::randInt(0, static_cast<int>(cells.size()) - 1);
        int i = 0;
        for (auto *cell: unknownCells) {
            nextCell = cell;
            if (i == randCell) {
                break;
            }
            i++;
        }
    }

    goToCell(nextCell, true);
}
