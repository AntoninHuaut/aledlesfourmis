#include "../../header/ant/Worker.h"

bool Worker::hasEatFood(double amountToEat) {
    double foodAtStart = this->foodCarriedAmount;
    double foodAfterEating = max(0.0, foodAtStart - amountToEat);
    double foodEaten = foodAtStart - foodAfterEating;
    this->foodCarriedAmount -= foodEaten;
    double foodRemainToEat = amountToEat - foodEaten;

    if (foodRemainToEat > 0) {
        return this->hasEatFood(foodRemainToEat);
    }
    return true;
}
