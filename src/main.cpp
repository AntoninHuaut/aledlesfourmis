#include <iostream>
#include <ctime>
#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/map/BoardGenerator.h"
#include "../header/gui/GUIMain.h"

using namespace std;

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    Config::get(); // Force configuration to be loaded

    auto *board = BoardGenerator::generateBoard();
    auto *gui = new GUIMain(board);
    gui->start();

    return 0;
}
