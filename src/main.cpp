#include <iostream>
#include <ctime>
#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/ant/Queen.h"
#include "../header/map/BoardGenerator.h"

using namespace std;

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)

    auto *test = BoardGenerator::generateBoard();

//    BoardCell *cell = new BasicCell(5);
//    auto *antQueen = new Queen();
//
//    antQueen->setCell(cell);
//    antQueen->tick();
//    std::cout << antQueen->getCurrentCell()->getMaxAntOnCell() << std::endl;
    return 0;
}
