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
    // TODO
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
    // TODO refill pheromoneAmount to ?
}

void Worker::putPheromones() {
    // TODO
}
