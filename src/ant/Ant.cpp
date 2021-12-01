#include "../../header/ant/Ant.h"
#include "../../header/map/BoardCell.h"
#include "../../header/map/Board.h"

double Ant::colonyFood = 0;

Ant::~Ant() {
    delete cellTraveledSinceColony;
}

Ant::Ant(int hoursBeforeDeath, int maxDaysWithoutFeeding,
         double foodConsumedEachDay, BoardCell *currentCell, AntType antType) {
    this->hoursBeforeDeath = hoursBeforeDeath;
    this->maxHoursWithoutFeeding = maxDaysWithoutFeeding * 24;
    this->foodConsumedEachDay = foodConsumedEachDay;
    this->currentCell = currentCell;
    this->antType = antType;

    this->currentCell->addAntOnCell(this);
}

int Ant::getAntTileNumber() {
    int tile = BLACK_ANT;

    if (!cellTraveledSinceColony->empty()) {

        BoardCell *lastCell = cellTraveledSinceColony->back();
        int lengthDiff = currentCell->getPosLength() - lastCell->getPosLength();
        int heightDiff = currentCell->getPosHeight() - lastCell->getPosHeight();

        if (lengthDiff == 1 && heightDiff == 0) tile += 1;
        else if (lengthDiff == 1 && heightDiff == 1) tile += 2;
        else if (lengthDiff == 0 && heightDiff == 1) tile += 3;
        else if (lengthDiff == -1 && heightDiff == 1) tile += 4;
        else if (lengthDiff == -1 && heightDiff == 0) tile += 5;
        else if (lengthDiff == -1 && heightDiff == -1) tile += 6;
        else if (lengthDiff == 0 && heightDiff == -1) tile += 7;
    }

    return tile;
}

list<BoardCell *> *Ant::getAvailableCellToMove(Board *board) {
    if (currentCell == nullptr)
        return new list<BoardCell *>;

    auto *cells = new list<BoardCell *>;

    auto *nearbyCells = board->getNearbyCells(this->currentCell);

    for (auto const &cell: *nearbyCells) {
        if (cell->getBoardCellType() != RockCellType && cell->haveSpace()) {
            cells->push_back(cell);
        }
    }

    //free(nearbyCells);

    return cells;
}

void Ant::goToCell(BoardCell *newCell) {
    this->currentCell->removeAntOnCell(this);
    this->addCellTraveled(this->currentCell);

    newCell->addAntOnCell(this);
    this->currentCell = newCell;
}

bool Ant::hasEatFood(double amountToEat) { // Default this->foodConsumedEachDay
    if (Ant::colonyFood >= amountToEat) {
        Ant::colonyFood -= amountToEat;
        return true;
    }

    return false;
}

bool Ant::isDyingHunger() {
    return hoursSinceLastFeeding >= maxHoursWithoutFeeding;
}

void Ant::genericEatFood() {
    bool _hasEatFood = hasEatFood();
    if (_hasEatFood) {
        hoursSinceLastFeeding = 0;
    }

    if (isDyingHunger()) {
        this->kill();
    }
}

