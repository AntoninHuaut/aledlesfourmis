#include "../../header/ant/Scout.h"
#include "../../header/map/Board.h"

void Scout::tickMove(Board *board) {

    auto *cells = getAvailableCellToMove(board);

    if(cells->empty()) return;

    auto *unKnownCells = new list<BoardCell *>;

    for (auto const &cell: *cells) {
        if (!cell->isVisited()){
            unKnownCells->push_back(cell);
        }
    }

    BoardCell *nextCell = nullptr;

    if(!unKnownCells->empty()){
        auto l_front = unKnownCells->begin();
        std::advance(l_front, CustomRandom::randInt(0, unKnownCells->size()-1));
        nextCell = *l_front;
    } else {
        auto l_front = cells->begin();
        std::advance(l_front, CustomRandom::randInt(0, cells->size()-1));
        nextCell = *l_front;
    }

    if(nextCell != nullptr){
        goToCell(nextCell, true);
    }

}
