#include "../../header/ant/Worker.h"
#include "../../header/map/BoardCell.h"
#include "../../header/map/BasicCell.h"

bool Worker::eatFood(float amountToEat) {
    double foodAtStart = this->foodCarriedAmount;
    double foodAfterEating = max(0.0, foodAtStart - amountToEat);
    double foodEaten = foodAtStart - foodAfterEating;
    this->foodCarriedAmount -= foodEaten;
    double foodRemainToEat = amountToEat - foodEaten;

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

    double maxToTake = basicCell->getFoodAmount() - foodCarriedAmount;
    if (maxToTake > 0) {
        basicCell->setFoodAmount(basicCell->getFoodAmount() - maxToTake);
        foodCarriedAmount += maxToTake;
    }
}

void Worker::dropFood() {
    // TODO drop food on cell if basicCell or in colony if colonyCell
}
