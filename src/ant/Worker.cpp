#include "../../header/ant/Worker.h"
#include "../../header/map/BoardCell.h"
#include "../../header/map/BasicCell.h"

bool Worker::eatFood(float amountToEat) {
    float foodAtStart = this->foodCarriedAmount;
    float foodAfterEating = max(0.f, foodAtStart - amountToEat);
    float foodEaten = foodAtStart - foodAfterEating;
    this->foodCarriedAmount -= foodEaten;
    float foodRemainToEat = amountToEat - foodEaten;

    if (foodRemainToEat > 0) {
        return Ant::eatFood(foodRemainToEat);
    }
    return true;
}

void Worker::tickMove(Board *board) {

    if (goingHome) {

        goBackToLastCell();

        if (foodCarriedAmount > 0) {
            putPheromones();
        }

        if (getCurrentCell()->getBoardCellType() == ColonyCellType) {
            visitColony();
            cellTraveledSinceStart->clear();
            goingHome = false;
        }


    } else {

        goCollectFood(board);
        //try pick food if have on the cell
        pickFood();

    }
}

void Worker::pickFood() {
    if (foodCarriedAmount >= Config::get()->getWorkerMaxFoodAmountCanCarried()) return; // Can't pick food because full
    if (getCurrentCell()->getBoardCellType() != BasicCellType) return; // No food on the cell

    auto *basicCell = dynamic_cast<BasicCell *>(getCurrentCell());
    if (basicCell->getFoodAmount() <= 0) return; // No food on the cell

    float maxToTake = basicCell->getFoodAmount() - foodCarriedAmount;
    if (maxToTake > 0) {
        basicCell->setFoodAmount(basicCell->getFoodAmount() - maxToTake);
        foodCarriedAmount += maxToTake;
        goingHome = true;
    }
}

void Worker::dropFood() {
    if (foodCarriedAmount <= 0) return;

    if (getCurrentCell()->getBoardCellType() == BasicCellType) {
        auto *basicCell = dynamic_cast<BasicCell *>(getCurrentCell());
        basicCell->setFoodAmount(basicCell->getFoodAmount() + foodCarriedAmount);
        foodCarriedAmount = 0;
    } else if (getCurrentCell()->getBoardCellType() == ColonyCellType) {
        colonyFood += foodCarriedAmount;
        foodCarriedAmount = 0;
    }
}

void Worker::visitColony() {
    if (getCurrentCell()->getBoardCellType() == ColonyCellType) {
        dropFood();
    }

    pheromoneAmount = Config::get()->getMaxAntPheromoneAmount();
}

void Worker::putPheromones() {
    auto *currentCell = getCurrentCell();
    if (pheromoneAmount <= 0) return;
    if (currentCell->getBoardCellType() != BasicCellType) return;

    float pheromonePercent = pheromoneAmount * Config::get()->getMaxAntPheromoneDropPercent();
    pheromoneAmount -= pheromonePercent;
    currentCell->addPheromone(pheromonePercent);
}

void Worker::goCollectFood(Board *board) {

    auto possibleCells = this->getAvailableVisitedCellToMove(board);

    if (possibleCells.empty()) return;

    //Search if food nearby first
    BoardCell *nearByFood = nullptr;
    for (auto cell: possibleCells) {
        if (cell->getBoardCellType() == BasicCellType) {
            if (dynamic_cast<BasicCell *>(cell)->getFoodAmount() > 0) {
                nearByFood = cell;
            }
        }
    }

    if (nearByFood == nullptr) {
        BoardCell *cell = getNextCellToFood(board);
        if (cell != nullptr) {
            goToCell(cell);
        }
    } else {
        goToCell(nearByFood);
    }

}


BoardCell *Worker::getNextCellToFood(Board *board) {
    auto availableCells = getAvailableVisitedCellToMove(board);
    if (availableCells.empty()) return nullptr;

    if (cellTraveledSinceStart->empty()) {
        return getCellWithMaxPheromoneOrRandom(availableCells);

    } else {
        auto directionalCells = getDirectionalCells(board);

        if (!directionalCells.empty()) {
            return getCellWithMaxPheromoneOrRandom(directionalCells);
        } else {
            //Case possible sans la derniere case visite
            availableCells.remove(cellTraveledSinceStart->back());
            return getCellWithMaxPheromoneOrRandom(availableCells);
        }
    }
}

list<BoardCell *> Worker::getDirectionalCells(Board *board) {
    list<BoardCell *> directionalCells;

    if (cellTraveledSinceStart->empty()) return directionalCells;

    int lengthDiff = cellTraveledSinceStart->back()->getPosLength() - this->getCurrentCell()->getPosLength();
    int heightDiff = cellTraveledSinceStart->back()->getPosHeight() - this->getCurrentCell()->getPosHeight();

    if (lengthDiff == 0 && heightDiff == 0) return directionalCells;

    auto availableCells = getAvailableVisitedCellToMove(board);

    if (lengthDiff == 0) {
        for (auto const &cell: availableCells) {
            int currentHeightDiff = cell->getPosHeight() - this->getCurrentCell()->getPosHeight();
            if (currentHeightDiff == -heightDiff) {
                directionalCells.push_back(cell);
            }
        }
    } else if (heightDiff == 0) {
        for (auto const &cell: availableCells) {
            int currentLengthDiff = cell->getPosLength() - this->getCurrentCell()->getPosLength();
            if (currentLengthDiff == -lengthDiff) {
                directionalCells.push_back(cell);
            }
        }
    } else {
        for (auto const &cell: availableCells) {
            int currentHeightDiff = cell->getPosHeight() - this->getCurrentCell()->getPosHeight();
            int currentLengthDiff = cell->getPosLength() - this->getCurrentCell()->getPosLength();

            if (currentLengthDiff != lengthDiff && currentHeightDiff != heightDiff) {
                if (currentHeightDiff != 0 && currentLengthDiff != 0) {
                    directionalCells.push_back(cell);
                }
            }
        }
    }
    return directionalCells;
}

BoardCell *Worker::getCellWithMaxPheromoneOrRandom(list<BoardCell *> cells) {

    if (cells.empty()) return nullptr;

    BoardCell *cellWithMaxPheromone = cells.front();
    int randCellIndex = CustomRandom::randInt(0, static_cast<int>(cells.size() - 1));
    BoardCell *randCell = nullptr;

    int i = 0;
    for (auto cell: cells) {
        if (i == randCellIndex) {
            randCell = cell;
        }

        if (cellWithMaxPheromone->getPheromone() < cell->getPheromone()) {
            cellWithMaxPheromone = cell;
        }
        i++;
    }

    if (cellWithMaxPheromone->getPheromone() > 0) {
        return cellWithMaxPheromone;
    } else {
        return randCell;
    }
}
