#include "../../header/ant/Ant.h"
#include "../../header/map/BoardCell.h"
#include "../../header/map/Board.h"

double Ant::colonyFood = 0;

Ant::Ant(int hoursBeforeDeath, int maxDaysWithoutFeeding,
         double foodConsumedEachDay, BoardCell *currentCell, AntType antType) {
    this->hoursBeforeDeath = hoursBeforeDeath;
    this->maxHoursWithoutFeeding = maxDaysWithoutFeeding * 24;
    this->foodConsumedEachDay = foodConsumedEachDay;
    this->currentCell = currentCell;
    this->antType = antType;

    this->currentCell->addAntOnCell(this);
}

Ant::~Ant() {
    this->currentCell->removeAntOnCell(this);
    delete cellTraveledSinceColony;
}

void Ant::kill() {
    setAlive(false);
}

int Ant::getAntTileNumber() {
    int tile = BLACK_ANT;

    if (this->lastCell != nullptr) {

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

list<BoardCell *> Ant::getAvailableCellToMove(Board *board) {
    if (currentCell == nullptr) return {};

    list<BoardCell *> cells;
    auto nearbyCells = board->getNearbyCells(this->currentCell);

    for (auto const &cell: nearbyCells) {
        if (cell->getBoardCellType() != RockCellType && cell->haveSpace()) {
            cells.push_back(cell);
        }
    }

    return cells;
}

void Ant::goToCell(BoardCell *newCell, bool haveToVisit) {
    this->currentCell->removeAntOnCell(this);
    this->addCellTraveled(this->currentCell);
    this->lastCell = this->currentCell;

    newCell->addAntOnCell(this);

    if (haveToVisit) {
        newCell->setVisited(true);
    }

    this->currentCell = newCell;
}

bool Ant::goBackToLastCell() {

    if (cellTraveledSinceColony->empty()) return false;

    if (cellTraveledSinceColony->back()->haveSpace()) {
        this->lastCell = this->currentCell;
        this->currentCell->removeAntOnCell(this);
        cellTraveledSinceColony->back()->addAntOnCell(this);
        this->currentCell = cellTraveledSinceColony->back();

        cellTraveledSinceColony->pop_back();
        return true;
    }

    return false;
}

void Ant::tick(Board *board) {
    // Ticking Age
    if (--hoursBeforeDeath <= 0) {
        kill();
        return;
    }

    // Ticking movement (empty by default)
    tickMove(board);

    // Ticking food
    tickFood();
}

bool Ant::hasEatFood(double amountToEat) {
    if (Ant::colonyFood >= amountToEat) {
        Ant::colonyFood -= amountToEat;
        return true;
    }

    return false;
}

bool Ant::isDyingHunger() const {
    return hoursSinceLastFeeding >= maxHoursWithoutFeeding;
}

void Ant::tickFood() {
    bool _hasEatFood = hasEatFood(this->foodConsumedEachDay);
    if (_hasEatFood) {
        hoursSinceLastFeeding = 0;
    }

    if (isDyingHunger()) {
        this->kill();
    }
}
