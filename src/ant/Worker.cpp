#include "../../include/ant/Worker.h"
#include "../../include/map/BoardCell.h"
#include "../../include/map/BasicCell.h"
#include "../../include/map/Board.h"

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

        if (foodCarriedAmount > 0) {
            putPheromones();
        }

        goBackToLastCell();

        if (getCurrentCell() == board->getCenterCell()) {
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

    float maxToTake = Config::get()->getWorkerMaxFoodAmountCanCarried() - foodCarriedAmount;
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
    dropFood();
    direction = sf::Vector2i(0, 0);
    pheromoneAmount = Config::get()->getMaxAntPheromoneAmount();
}

void Worker::putPheromones() {
    auto *currentCell = getCurrentCell();
    if (pheromoneAmount <= 0) return;
    if (currentCell->getBoardCellType() == RockCellType) return;

    float pheromonePercent = pheromoneAmount * Config::get()->getMaxAntPheromoneDropPercent();
    pheromoneAmount -= currentCell->addPheromone(pheromonePercent);
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
        BoardCell *cell = getNextCellToFood(board, possibleCells);
        if (cell != nullptr) {
            goToCell(cell);
        }
    } else {
        goToCell(nearByFood);
    }

}


BoardCell *Worker::getNextCellToFood(Board *board, const list<BoardCell *> &availableCells) {
    if (availableCells.empty()) return nullptr;

    int currLength = getCurrentCell()->getPosLength();
    int currHeight = getCurrentCell()->getPosHeight();

    if (direction.x == 0 && direction.y == 0) {

        BoardCell *cell = getCellWithMaxPheromoneOrRandom(availableCells, -1, -1);
        if (cell != nullptr) {
            direction.x = currLength - cell->getPosLength();
            direction.y = currHeight - cell->getPosHeight();
        }
        return cell;

    } else {

        list<BoardCell *> directionalCells;

        directionalCells = getDirectionalCells(board, availableCells, direction.x, direction.y);
        if (!directionalCells.empty()) {

            return getCellWithMaxPheromoneOrRandom(directionalCells, currLength + direction.x,
                                                   currHeight + direction.y);

        } else {

            goingHome = true;
            return nullptr;
        }
    }
}

list<BoardCell *>
Worker::getDirectionalCells(Board *board, const list<BoardCell *> &availableCells, int lengthDiff, int heightDiff) {
    list<BoardCell *> directionalCells;

    if (lengthDiff == 0 && heightDiff == 0) return directionalCells;

    if (lengthDiff == 0) {
        for (auto const &cell: availableCells) {
            int currentHeightDiff = cell->getPosHeight() - this->getCurrentCell()->getPosHeight();
            if (currentHeightDiff == heightDiff) {
                directionalCells.push_back(cell);
            }
        }
    } else if (heightDiff == 0) {
        for (auto const &cell: availableCells) {
            int currentLengthDiff = cell->getPosLength() - this->getCurrentCell()->getPosLength();
            if (currentLengthDiff == lengthDiff) {
                directionalCells.push_back(cell);
            }
        }
    } else {

        for (auto const &cell: availableCells) {
            int currentLengthDiff = cell->getPosLength() - this->getCurrentCell()->getPosLength();
            int currentHeightDiff = cell->getPosHeight() - this->getCurrentCell()->getPosHeight();

            if (currentLengthDiff != lengthDiff && currentHeightDiff != heightDiff) {
                directionalCells.push_back(cell);
            }
        }
    }
    return directionalCells;
}

BoardCell *
Worker::getCellWithMaxPheromoneOrRandom(const list<BoardCell *> &cells, int directionCellPosLenght,
                                        int directionCellPosHeight) {

    if (cells.empty()) return nullptr;

    BoardCell *cellWithMaxPheromone = nullptr;
    int randCellIndex = CustomRandom::randInt(0, static_cast<int>(cells.size() - 1));
    BoardCell *randCell = nullptr;
    BoardCell *directionalCell = nullptr;

    int i = 0;
    for (auto cell: cells) {
        if (cellWithMaxPheromone == nullptr) {
            cellWithMaxPheromone = cell;
        }

        if (i == randCellIndex) {
            randCell = cell;
        }

        if (cell->getPosLength() == directionCellPosLenght && cell->getPosHeight() == directionCellPosHeight) {
            directionalCell = cell;
        }

        if (cellWithMaxPheromone->getPheromone() < cell->getPheromone()) {
            cellWithMaxPheromone = cell;
        }
        i++;
    }

    if (cellWithMaxPheromone->getPheromone() > 0) {
        return cellWithMaxPheromone;
    } else {
        if (directionalCell != nullptr) {
            return directionalCell;
        }
        return randCell;
    }
}

void Worker::kill() {
    Ant::kill();

    dropFood();
}
