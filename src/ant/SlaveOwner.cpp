#include "../../header/ant/SlaveOwner.h"
#include "../../header/ant/Queen.h"
#include "../../header/map/Board.h"

void SlaveOwner::attackQueen(Board *board) {
    auto *queen = board->getAntQueen();
    if (queen == nullptr) return; // Queen is dead (it's the last turn of the game)
    if (queen->getCurrentCell() != getCurrentCell()) return;

    if (hoursSinceLastFeeding > 1) {
        if (eatFood(this->foodConsumedEachDay)) {
            hoursSinceLastFeeding = 0;
        }
    }

    if (larvaCarried >= Config::get()->getSlaveOwnerMaxLarvaCanCarried()) return;

    int maxLarvaToCatch = abs(Config::get()->getSlaveOwnerMaxLarvaCanCarried() - larvaCarried);

    int larvaCaught = board->catchLarva(maxLarvaToCatch);
    if (larvaCaught > 0) {
        queen->setAssaulted(true);
        larvaCarried += larvaCaught;
    }
}

void SlaveOwner::tickMove(Board *board) {
    if (!haveArrivedToColony) {
        goToCenter(board);
    } else if (larvaCarried == 0) {
        attackQueen(board);
    } else {
        goBackToLastCell();
    }
}

void SlaveOwner::tick(Board *board) {
    Ant::tick(board);

    if (cellTraveledSinceStart->empty()) {
        kill();
    }
}

bool SlaveOwner::eatFood(float amountToEat) {
    if (getCurrentCell()->getBoardCellType() == ColonyCellType) {
        return Ant::eatFood(amountToEat);
    }

    if (getCurrentCell()->getBoardCellType() == BasicCellType) {
        auto *basicCell = dynamic_cast<BasicCell *>(getCurrentCell());
        if (basicCell->getFoodAmount() >= amountToEat) {
            basicCell->setFoodAmount(basicCell->getFoodAmount() - amountToEat);
            return true;
        }

        return false;
    }

    return false;
}
