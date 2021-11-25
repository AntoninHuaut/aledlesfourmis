#include "../../header/map/BoardGenerator.h"

/* test */
#include <iostream>

void logBoardFile(BoardGenerator *boardGenerator) {
    ofstream outFile;
    outFile.open("mapTest.txt");

    for (int height = 0; height < Config::get()->getHeight(); height++) {
        for (int length = 0; length < Config::get()->getLength(); length++) {
            BoardCell *boardCell = boardGenerator->getBoard()->getCells()[height][length];
            BoardCellType boardCellType = boardCell->getBoardCellType();
            string type;

            if (boardCellType == RockCellType) {
                type = " X ";
            } else if (boardCellType == ColonyCellType) {
                type = " O ";
            } else if (boardCellType == BasicCellType) {
                auto *basicCell = dynamic_cast<BasicCell *>(boardCell);
                type = " " + to_string(basicCell->getFoodAmount()) + " ";
            } else {
                type = " ? ";
            }

            outFile << type;
        }

        outFile << "\n\n\n";
    }

    outFile.close();
}

/* */

Board *BoardGenerator::generateBoard() {
    auto *boardGenerator = BoardGenerator::createBoard();
    boardGenerator->generateRock();
    boardGenerator->generateBasicCell();
    boardGenerator->generateSmallFoodUnit();
    boardGenerator->generateBigFoodUnit();

    /* TODO TEST */
    logBoardFile(boardGenerator);
    /* END TEST */

    return boardGenerator->board;
}

void BoardGenerator::generateBigFoodUnit() {
    int posOne = randInt(4, 1); // 1 = NO, 2 = SO, 3 = NE, 4 = SE
    int posTwo = posOne;
    while (posTwo == posOne) {
        posTwo = randInt(4, 1);
    }

    int firstPosHeight = posOne == 1 % 2 == 1 ? 0 : Config::get()->getHeight() - 1;
    int firstPosLength = posOne <= 2 ? 0 : Config::get()->getLength() - 1;

    int secondPosHeight = posTwo == 1 % 2 == 1 ? 0 : Config::get()->getHeight() - 1;
    int secondPosLength = posTwo <= 2 ? 0 : Config::get()->getLength() - 1;

    generateBigFoodUnitCross(firstPosHeight, firstPosLength);
    generateBigFoodUnitCross(secondPosHeight, secondPosLength);
}

void BoardGenerator::generateBigFoodUnitCross(int searchPosHeight, int searchPosLength) {
    BasicCell *centerCell = findCellNearCoordinateWithCrossCellFree(searchPosHeight, searchPosLength);
    if (centerCell == nullptr) return;

    int heightCenter = centerCell->getPosHeight();
    int lengthCenter = centerCell->getPosLength();

    for (int padHeight = -1; padHeight <= 1; padHeight += 1) {
        for (int padLength = -1; padLength <= 1; padLength += 1) {
            if ((padHeight == -1 && padLength == -1)
                || (padHeight == -1 && padLength == 1)
                || (padHeight == 1 && padLength == -1)
                || (padHeight == 1 && padLength == 1)) {
                continue;
            }

            int posHeight = heightCenter + padHeight;
            int posLength = lengthCenter + padLength;

            if (!isValidCell(posHeight, posLength)) continue;
            if (!isValidBigFoodUnitCell(posHeight, posLength)) continue;

            auto *boardCell = board->getCells()[posHeight][posLength];
            auto *basicCell = dynamic_cast<BasicCell *>(boardCell);
            basicCell->setFoodAmount(Config::get()->getBigFoodUnitValue());
        }
    }
}

BasicCell *BoardGenerator::findCellNearCoordinateWithCrossCellFree(int height, int length) {
    int pad = 1;

    while (pad < ((Config::get()->getLength() + Config::get()->getHeight()) / 4)) {
        for (int padHeight = -pad; padHeight <= pad; padHeight++) {
            for (int padLength = -pad; padLength <= pad; padLength++) {
                if (padHeight == 0 && padLength == 0) continue;

                int posHeight = height + padHeight;
                int posLength = length + padLength;

                if (!isValidCell(posHeight, posLength)) continue;
                if (!isBasicCellsCrossEmpty(posHeight, posLength)) continue;

                auto *boardCell = board->getCells()[posHeight][posLength];
                auto *basicCell = dynamic_cast<BasicCell *>(boardCell);
                return basicCell;
            }
        }

        pad++;
    }

    return nullptr;
}

bool BoardGenerator::isBasicCellsCrossEmpty(int centerHeight, int centerLength) {
    for (int padHeight = -1; padHeight <= 1; padHeight += 1) {
        for (int padLength = -1; padLength <= 1; padLength += 1) {
            if ((padHeight == -1 && padLength == -1)
                || (padHeight == -1 && padLength == 1)
                || (padHeight == 1 && padLength == -1)
                || (padHeight == 1 && padLength == 1)) {
                continue;
            }

            if (!isValidBigFoodUnitCell(centerHeight + padHeight, centerLength + padLength)) {
                return false;
            }
        }
    }

    return true;
}

bool BoardGenerator::isValidBigFoodUnitCell(int height, int length) {
    if (!isValidCell(height, length)) return false;

    auto *boardCell = board->getCells()[height][length];
    if (boardCell->getBoardCellType() != BasicCellType) return false;

    auto *basicCell = dynamic_cast<BasicCell *>(boardCell);
    return basicCell->getFoodAmount() == 0;
}

void BoardGenerator::generateSmallFoodUnit() {
    int amountFoodUnit = (int) round(
            Config::get()->getLength() * Config::get()->getHeight() * Config::get()->getFoodPercent());
    int totalFoodUnitGenerated = 0;

    int randLengthMin = 0, randHeightMin = 0;
    int randLengthMax = Config::get()->getLength() - 1, randHeightMax = Config::get()->getHeight() - 1;

    BoardCell ***cells = this->getBoard()->getCells();

    while (totalFoodUnitGenerated < amountFoodUnit) {
        int centerFoodHeight = randInt(randHeightMax, randHeightMin);
        int centerFoodLength = randInt(randLengthMax, randLengthMin);
        BoardCell *cell = cells[centerFoodHeight][centerFoodLength];

        // If a cell not exist or not a BasicCell, skip to next random cell
        if (cell == nullptr || cell->getBoardCellType() != BasicCellType) continue;

        // If there are some food nearby, skip generation of food on the current cell
        if (hasFoodNeighbor(centerFoodHeight, centerFoodLength)) continue;

        // Setting food
        auto *basicCell = dynamic_cast<BasicCell *>(cell);
        basicCell->setFoodAmount(Config::get()->getSmallFoodUnitValue());

        totalFoodUnitGenerated++;
    }
}

void BoardGenerator::generateRock() {
    int amountRock = (int) round(
            Config::get()->getLength() * Config::get()->getHeight() * Config::get()->getRockPercent());
    int totalRockGenerated = 0;

    int randLengthMin = 0, randHeightMin = 0;
    int randLengthMax = Config::get()->getLength() - 1, randHeightMax = Config::get()->getHeight() - 1;

    BoardCell ***cells = this->getBoard()->getCells();

    while (totalRockGenerated < amountRock) {
        int centerRockHeight = randInt(randHeightMax, randHeightMin);
        int centerRockLength = randInt(randLengthMax, randLengthMin);
        BoardCell *cell = cells[centerRockHeight][centerRockLength];

        // If a cell already exist, skip to next random cell
        if (cell != nullptr) continue;

        // If there are some rocks nearby, skip generation of rock on the current cell
        if (hasRockNeighbor(centerRockHeight, centerRockLength)) continue;

        // Creating a new rock
        cells[centerRockHeight][centerRockLength] = new RockCell(centerRockLength, centerRockHeight);
        totalRockGenerated++;

        // Generating how many rock will be near the rock
        int rPercent = randInt(100, 1);
        int additionalRockNear;
        if (rPercent <= 1) additionalRockNear = 5;
        else if (rPercent <= 5) additionalRockNear = 4;
        else if (rPercent <= 10) additionalRockNear = 3;
        else if (rPercent <= 20) additionalRockNear = 2;
        else if (rPercent <= 50) additionalRockNear = 1;
        else additionalRockNear = 0;

        // Generating neighbor rocks
        int additionalRockGenerated = 0;
        int nbTry = 0;
        while (additionalRockGenerated < additionalRockNear && nbTry++ <= 100) {
            int heightDelta = randInt(1, -1);
            int lengthDelta = randInt(1, -1);

            int posRockHeight = centerRockHeight + heightDelta;
            int posRockLength = centerRockLength + lengthDelta;

            if (!isValidCell(posRockHeight, posRockLength)) continue;

            BoardCell *posCell = cells[posRockHeight][posRockLength];

            if (posCell == nullptr) {
                cells[posRockHeight][posRockLength] = new RockCell(posRockHeight, posRockLength);

                additionalRockGenerated++;
                totalRockGenerated++;
            }
        }
    }
}

void BoardGenerator::generateBasicCell() {
    for (int height = 0; height < Config::get()->getHeight(); height++) {
        for (int length = 0; length < Config::get()->getLength(); length++) {
            BoardCell ***cells = getBoard()->getCells();
            if (cells[height][length] == nullptr) {
                cells[height][length] = new BasicCell(length, height);
            }
        }
    }
}

BoardGenerator *BoardGenerator::createBoard() {
    auto ***cells2D = (BoardCell ***) calloc(Config::get()->getHeight(), sizeof(BoardCell **));

    if (cells2D == nullptr) {
        throw invalid_argument("Failed to allocate BoardCell**");
    }

    for (int i = 0; i < Config::get()->getHeight(); i++) {
        auto **cellsLine = (BoardCell **) calloc(Config::get()->getLength(),
                                                 sizeof(BoardCell *)); // NOLINT(bugprone-sizeof-expression)

        if (cellsLine == nullptr) {
            throw invalid_argument("Failed to allocate BoardCell*");
        }

        for (int j = 0; j < Config::get()->getLength(); j++) {
            cellsLine[j] = nullptr;
        }

        cells2D[i] = cellsLine;
    }

    auto *board = new Board(cells2D);
    return new BoardGenerator(board);
}

bool BoardGenerator::hasFoodNeighbor(int height, int length) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int tmpHeight = height + i;
            int tmpLength = length + j;
            if (!isValidCell(tmpHeight, tmpLength)) continue;

            BoardCell *nearbyCell = this->board->getCells()[tmpHeight][tmpLength];
            if (nearbyCell != nullptr && nearbyCell->getBoardCellType() == BasicCellType) {
                auto *basicCell = dynamic_cast<BasicCell *>(nearbyCell);
                if (basicCell->getFoodAmount() > 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool BoardGenerator::hasRockNeighbor(int height, int length) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 || j == 0) continue;

            int tmpHeight = height + i;
            int tmpLength = length + j;
            if (!isValidCell(tmpHeight, tmpLength)) continue;

            BoardCell *nearbyCell = this->board->getCells()[tmpHeight][tmpLength];
            if (nearbyCell != nullptr && nearbyCell->getBoardCellType() == RockCellType) {
                return true;
            }
        }
    }
    return false;
}

bool BoardGenerator::isValidCell(int height, int length) {
    return height >= 0 && height < Config::get()->getHeight() && length >= 0 && length < Config::get()->getLength();
}

int BoardGenerator::randInt(int maxInclusive, int minInclusive) {
    return rand() % (maxInclusive - minInclusive + 1) + minInclusive; // NOLINT(cert-msc50-cpp)
}