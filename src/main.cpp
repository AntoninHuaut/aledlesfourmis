#include <iostream>
#include "../header/BoardCell.h"
#include "../header/BasicCell.h"
#include "../header/Queen.h"

int main() {

    BoardCell* cell = new BasicCell(5);
    auto* antQueen = new Queen();

    antQueen->setCell(cell);
    antQueen->tick();
    std::cout << antQueen->getCurrentCell()->getMaxAntOnCell() << std::endl;
    return 0;
}
