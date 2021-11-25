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
        int centerRockHeight = rand() % (randHeightMax - randHeightMin + 1) + randHeightMin; // NOLINT(cert-msc50-cpp)
        int centerRockLength = rand() % (randLengthMax - randLengthMin + 1) + randLengthMin; // NOLINT(cert-msc50-cpp)
        BoardCell *cell = cells[centerRockHeight][centerRockLength];

        if (cell == nullptr) {
            cells[centerRockHeight][centerRockLength] = new RockCell(centerRockLength, centerRockHeight);
            totalRockGenerated++;

            int rPercent = rand() % 100; // NOLINT(cert-msc50-cpp)
            int additionalRockNear;
            if (rPercent <= 1) {
                additionalRockNear = 5;
            } else if (rPercent <= 5) {
                additionalRockNear = 4;
            } else if (rPercent <= 10) {
                additionalRockNear = 3;
            } else if (rPercent <= 20) {
                additionalRockNear = 2;
            } else if (rPercent <= 50) {
                additionalRockNear = 1;
            } else {
                additionalRockNear = 0;
            }

            int additionalRockGenerated = 0;
            int nbTry = 0;
            while (additionalRockGenerated < additionalRockNear && nbTry++ <= 100) {
                int lengthDelta = (rand() % 2) - 1; // NOLINT(cert-msc50-cpp)
                int heightDelta = (rand() % 2) - 1; // NOLINT(cert-msc50-cpp)

                int possibleRockHeight = centerRockHeight + heightDelta;
                int possibleRockLength = centerRockLength + lengthDelta;

                if (possibleRockHeight < 0 || possibleRockHeight >= Config::HEIGHT) continue;
                if (possibleRockLength < 0 || possibleRockLength >= Config::LENGTH) continue;

                BoardCell *possibleCell = cells[possibleRockHeight][possibleRockLength];

                if (possibleCell == nullptr) {
                    cells[possibleRockHeight][possibleRockLength] =
                            new RockCell(possibleRockHeight, possibleRockLength);
                    additionalRockGenerated++;
                    totalRockGenerated++;
                }
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
        auto **cellsLine = (BoardCell **) calloc(Config::LENGTH, sizeof(BoardCell *));

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