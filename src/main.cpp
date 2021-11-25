#include <iostream>
#include <ctime>
#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/map/BoardGenerator.h"
#include "../header/gui/GUIMain.h"


using namespace std;


int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)

    auto *test = BoardGenerator::generateBoard();

    auto *gui = new GUIMain(test);

    gui->start();

    return 0;
}
