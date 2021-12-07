#include "../../header/ant/Soldier.h"
#include "../../header/ant/SlaveOwner.h"
#include "../../header/map/BoardCell.h"
#include "../../header/map/BoardGenerator.h"

void Soldier::moveSoldier(Board *board) {
    auto cells = getAvailableVisitedCellToMove(board);

    // Priority: track SlaveOwner
    for (auto *checkCell: cells) {
        for (auto *ant: *checkCell->getAntOnCell()) {
            if (ant->getAntType() == SlaveOwnerType && ant->isAlive()) {
                goToCell(checkCell);
                return;
            }
        }
    }

    // Else, move random if the soldier don't have to go to the colony
    if (tickSinceColonyVisited < Config::get()->getSoldierHoursBeforeVisitColony()) {
        auto randomCell = cells.begin();
        std::advance(randomCell, CustomRandom::randInt(0, static_cast<int>(cells.size()) - 1));

        BoardCell *cellToMove = *randomCell;
        goToCell(cellToMove);
    } else {
        goBackToLastCell(); // TODO goToCenter after rework

        if (getCurrentCell()->getBoardCellType() == ColonyCellType) {
            tickSinceColonyVisited = 0;
            cellTraveledSinceStart->clear();
        }
    }
}

void Soldier::tickMove(Board *board) {
    moveSoldier(board);
    attackOneSlaveOwnerNearCell(board, getCurrentCell());

    tickSinceColonyVisited++;
}

void Soldier::attackOneSlaveOwnerNearCell(Board *board, BoardCell *cell) {
    for (int padHeight = -1; padHeight <= 1; padHeight += 1) {
        for (int padLength = -1; padLength <= 1; padLength += 1) {
            int posHeight = cell->getPosHeight() + padHeight;
            int posLength = cell->getPosLength() + padLength;

            if (!BoardGenerator::isValidCell(posHeight, posLength)) continue;

            auto *checkCell = board->getCells()[posHeight][posLength];

            for (auto *ant: *checkCell->getAntOnCell()) {
                if (ant->getAntType() == SlaveOwnerType && ant->isAlive()) {
                    auto slaveOwner = dynamic_cast<SlaveOwner *>(ant);

                    float randomLuck = ((float) CustomRandom::randInt(0, 100) / 100.f);
                    if (randomLuck <= Config::get()->getSoldierPercentToKillSlaveOwner()) {
                        board->getAntQueen()->createChildAndExpand(board, slaveOwner->getLarvaCarried());
                        slaveOwner->kill();
                    }
                    return;
                }
            }
        }
    }
}