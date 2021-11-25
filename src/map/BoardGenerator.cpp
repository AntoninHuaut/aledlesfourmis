#include "../../header/map/BoardGenerator.h"

/* test */
#include <fstream>
#include <iostream>

void logBoardFile(BoardGenerator *boardGenerator) {
    ofstream outFile;
    outFile.open("mapTest.txt");

    for (int height = 0; height < Config::HEIGHT; height++) {
        for (int length = 0; length < Config::LENGTH; length++) {
            BoardCell *boardCell = boardGenerator->getBoard()->getCells()[height][length];
            BoardCellType boardCellType = boardCell->getBoardCellType();
            string type;

            if (boardCellType == RockCellType) {
                type = "X";
            } else if (boardCellType == ColonyCellType) {
                type = "O";
            } else if (boardCellType == BasicCellType) {
                type = ".";
            } else {
                type = "?";
            }

            outFile << type;
        }

        outFile << "\n";
    }

    outFile.close();
}

/* */

Board *BoardGenerator::generateBoard() {
    auto *boardGenerator = BoardGenerator::createBoard();
    boardGenerator->generateRock();
    boardGenerator->generateBasicCell();
    // TODO

    /* TODO TEST */
    logBoardFile(boardGenerator);
    /* END TEST */

    return boardGenerator->board;
}

void BoardGenerator::generateRock() {
    int amountRock = (int) round(Config::LENGTH * Config::HEIGHT * Config::ROCK_PERCENT);
    int totalRockGenerated = 0;

    int randLengthMin = 0, randHeightMin = 0;
    int randLengthMax = Config::LENGTH - 1, randHeightMax = Config::HEIGHT - 1;

    BoardCell ***cells = this->getBoard()->getCells();

    while (totalRockGenerated < amountRock) {
        int centerRockHeight = randInt(randHeightMax, randHeightMin);
        int centerRockLength = randInt(randLengthMax, randLengthMin);
        BoardCell *cell = cells[centerRockHeight][centerRockLength];

        // If a cell already exist, skip to next random cell
        if (cell != nullptr) continue;

        // Checking if there are already some rocks nearby
        bool hasRockNearby = false;
        for (int i = -1; i <= 1 && !hasRockNearby; i++) {
            for (int j = -1; j <= 1 && !hasRockNearby; j++) {
                int tmpHeight = centerRockHeight + i;
                int tmpLength = centerRockLength + j;
                if (!isValidCell(tmpHeight, tmpLength)) continue;

                BoardCell *nearbyCell = cells[centerRockHeight][centerRockLength];
                if (nearbyCell != nullptr && nearbyCell->getBoardCellType() == RockCellType) {
                    hasRockNearby = true;
                }
            }
        }

        // If there is at least one rock, skip generation of rock on the current cell
        if (hasRockNearby) continue;

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
    for (int height = 0; height < Config::HEIGHT; height++) {
        for (int length = 0; length < Config::LENGTH; length++) {
            BoardCell ***cells = getBoard()->getCells();
            if (cells[height][length] == nullptr) {
                cells[height][length] = new BasicCell(length, height);
            }
        }
    }
}

BoardGenerator *BoardGenerator::createBoard() {
    auto ***cells2D = (BoardCell ***) calloc(Config::HEIGHT, sizeof(BoardCell **));

    if (cells2D == nullptr) {
        throw invalid_argument("Failed to allocate BoardCell**");
    }

    for (int i = 0; i < Config::HEIGHT; i++) {
        auto **cellsLine = (BoardCell **) calloc(Config::LENGTH,
                                                 sizeof(BoardCell *)); // NOLINT(bugprone-sizeof-expression)

        if (cellsLine == nullptr) {
            throw invalid_argument("Failed to allocate BoardCell*");
        }

        for (int j = 0; j < Config::LENGTH; j++) {
            cellsLine[j] = nullptr;
        }

        cells2D[i] = cellsLine;
    }

    auto *board = new Board(cells2D);
    return new BoardGenerator(board);
}

bool BoardGenerator::isValidCell(int height, int length) {
    return height >= 0 && height < Config::HEIGHT && length >= 0 && length < Config::LENGTH;
}

int BoardGenerator::randInt(int maxInclusive, int minInclusive) {
    return rand() % (maxInclusive - minInclusive + 1) + minInclusive; // NOLINT(cert-msc50-cpp)
}