#include "../../header/ant/SlaveOwner.h"
#include "../../header/map/Board.h"

int cellsDistance(BoardCell *cell1, BoardCell *cell2){
    return abs(cell1->getPosLength() - cell2->getPosLength()) + abs(cell1->getPosHeight() - cell2->getPosHeight());
}

void SlaveOwner::goToCenter(Board *board) {

    list<BoardCell*> *possibleCells = this->getAvailableCellToMove(board);

    cout << possibleCells->size() << endl;

    if(possibleCells->empty()) return;

    BoardCell *target = board->getCenterCell();

    int min = cellsDistance(possibleCells->front(), target);
    BoardCell *bestCell = possibleCells->front();


    for (auto *cell: *possibleCells) {

        int newDist = cellsDistance(cell, target);

        if(newDist <= min && find(this->cellTraveledSinceColony->begin(), this->cellTraveledSinceColony->end(), cell) == this->cellTraveledSinceColony->end()){
            min = newDist;
            bestCell = cell;
        }
    }

    this->goToCell(bestCell);

}

void SlaveOwner::tick(Board *board) {
    goToCenter(board);
}
