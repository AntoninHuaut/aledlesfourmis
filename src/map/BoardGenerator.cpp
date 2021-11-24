#include "../../header/map/BoardGenerator.h"

Board *BoardGenerator::generateBoard() {
    auto *boardGenerator = BoardGenerator::createBoard();
    boardGenerator->generateRock();
    // TODO

    return boardGenerator->board;
}

void BoardGenerator::generateRock() {
    int amountRock = BOARD_LENGTH * BOARD_HEIGHT * ROCK_PERCENT;
    int totalRockGenerated = 0;

    int randXMin = 0, randYMin = 0;
    int randXMax = BOARD_LENGTH - 1, randYMax = BOARD_HEIGHT - 1;

    while (totalRockGenerated < amountRock) {
        int nbRockGenerated = 0;
        int x = rand() % (randXMax - randXMin + 1) + randXMin; // NOLINT(cert-msc50-cpp)
        int y = rand() % (randYMax - randYMin + 1) + randYMin; // NOLINT(cert-msc50-cpp)

        totalRockGenerated += nbRockGenerated;
    }
}

BoardGenerator *BoardGenerator::createBoard() {
    auto ***cells2D = (BoardCell ***) malloc(sizeof(BoardCell **) * BOARD_HEIGHT); // NOLINT(bugprone-sizeof-expression)

    if (cells2D == nullptr) {
        throw invalid_argument("Failed to allocate BoardCell**");
    }

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        auto **cellsLine = (BoardCell **) malloc(
                sizeof(BoardCell *) * BOARD_LENGTH); // NOLINT(bugprone-sizeof-expression)

        if (cellsLine == nullptr) {
            throw invalid_argument("Failed to allocate BoardCell*");
        }

        cells2D[i] = cellsLine;

        //cellsLine[i] = new BoardCell(0); // TODO TEST
    }

    auto *board = new Board(cells2D);
    return new BoardGenerator(board);
}
