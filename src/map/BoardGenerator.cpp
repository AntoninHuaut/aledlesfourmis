#include "../../header/map/BoardGenerator.h"
#include "../../header/ant/SlaveOwner.h"

Board *BoardGenerator::generateBoard() {
    auto *boardGenerator = BoardGenerator::createBoard();
    boardGenerator->generateRock();
    boardGenerator->generateBasicCell();
    boardGenerator->generateSmallFoodUnit();
    boardGenerator->generateBigFoodUnit();
    boardGenerator->generateColony();

    return boardGenerator->board;
}

void BoardGenerator::generateBigFoodUnit() {
    int posOne = CustomRandom::randInt(1, 4); // 1 = NO, 2 = SO, 3 = NE, 4 = SE
    int posTwo = posOne;
    while (posTwo == posOne) {
        posTwo = CustomRandom::randInt(1, 4);
    }

    int firstPosHeight = (posOne % 2) == 1 == 1 ? 0 : Config::get()->getHeight() - 1;
    int firstPosLength = posOne <= 2 ? 0 : Config::get()->getLength() - 1;

    int secondPosHeight = (posTwo % 2) == 1 == 1 ? 0 : Config::get()->getHeight() - 1;
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
    auto boardHeight = Config::get()->getHeightFloat();
    auto boardLength = Config::get()->getLengthFloat();
    int amountFoodUnit = (int) round(boardHeight * boardLength * Config::get()->getFoodPercent());
    int totalFoodUnitGenerated = 0;

    int randLengthMin = 0, randHeightMin = 0;
    int randLengthMax = Config::get()->getLength() - 1, randHeightMax = Config::get()->getHeight() - 1;

    auto ***cells = this->getBoard()->getCells();

    while (totalFoodUnitGenerated < amountFoodUnit) {
        int centerFoodHeight = CustomRandom::randInt(randHeightMin, randHeightMax);
        int centerFoodLength = CustomRandom::randInt(randLengthMin, randLengthMax);
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
    auto boardHeight = Config::get()->getHeightFloat();
    auto boardLength = Config::get()->getLengthFloat();
    int amountRock = (int) round(boardHeight * boardLength * Config::get()->getRockPercent());
    int totalRockGenerated = 0;

    int randLengthMin = 0, randHeightMin = 0;
    int randLengthMax = Config::get()->getLength() - 1, randHeightMax = Config::get()->getHeight() - 1;

    auto ***cells = this->getBoard()->getCells();

    while (totalRockGenerated < amountRock) {
        int centerRockHeight = CustomRandom::randInt(randHeightMin, randHeightMax);
        int centerRockLength = CustomRandom::randInt(randLengthMin, randLengthMax);
        auto *cell = cells[centerRockHeight][centerRockLength];

        // If a cell already exist, skip to next random cell
        if (cell != nullptr) continue;

        // If there are some rocks nearby, skip generation of rock on the current cell
        if (hasRockNeighbor(centerRockHeight, centerRockLength)) continue;

        // Creating a new rock
        cells[centerRockHeight][centerRockLength] = new RockCell(centerRockLength, centerRockHeight);
        totalRockGenerated++;

        // Generating how many rock will be near the rock
        int rPercent = CustomRandom::randInt(1, 100);
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
            int heightDelta = CustomRandom::randInt(-1, 1);
            int lengthDelta = CustomRandom::randInt(-1, 1);

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
            auto ***cells = getBoard()->getCells();
            if (cells[height][length] == nullptr) {
                cells[height][length] = new BasicCell(length, height);
            }
        }
    }
}

void BoardGenerator::generateColony() {
    int centerHeight = Config::get()->getHeight();
    centerHeight = (centerHeight - (centerHeight % 2)) / 2;
    int centerLength = Config::get()->getLength();
    centerLength = (centerLength - (centerLength % 2)) / 2;

    auto ***cells = board->getCells();
    auto *centerCell = cells[centerHeight][centerLength];
    if (centerCell != nullptr) {
        delete centerCell;
        cells[centerHeight][centerLength] = nullptr;
    }

    auto *colonyCell = new ColonyCell(centerLength, centerHeight);
    cells[centerHeight][centerLength] = colonyCell;
    board->addColoniesCell(colonyCell);
    board->setAntQueen(new Queen(colonyCell));

    /* TODO TEST */
    auto *firstCell = cells[0][0];
    auto ant = new SlaveOwner(firstCell);
    firstCell->addAntOnCell(ant);
    board->addAntList(ant);
    /* */

    removeRockNearColony(centerHeight, centerLength);
}

void BoardGenerator::removeRockNearColony(int centerHeight, int centerLength) {
    auto ***cells = board->getCells();

    for (int iHeight = -1; iHeight <= 1; iHeight++) {
        for (int iLength = -1; iLength <= 1; iLength++) {
            if (iHeight == 0 && iLength == 0) continue;

            int tmpHeight = centerHeight + iHeight;
            int tmpLength = centerLength + iLength;
            auto *neighborCell = cells[tmpHeight][tmpLength];

            if (neighborCell != nullptr && neighborCell->getBoardCellType() == RockCellType) {
                delete neighborCell;
                cells[tmpHeight][tmpLength] = new BasicCell(tmpLength, tmpHeight);
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

            auto *nearbyCell = this->board->getCells()[tmpHeight][tmpLength];
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

            auto *nearbyCell = this->board->getCells()[tmpHeight][tmpLength];
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
