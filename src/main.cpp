#include <iostream>
#include <ctime>
#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/ant/Queen.h"
#include "../header/map/BoardGenerator.h"
#include <SFML/Graphics.hpp>

using namespace std;

void createInterface() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)

//    auto *test = BoardGenerator::generateBoard();

//    BoardCell *cell = new BasicCell(5);
//    auto *antQueen = new Queen();
//
//    antQueen->setCell(cell);
//    antQueen->tick();
//    std::cout << antQueen->getCurrentCell()->getMaxAntOnCell() << std::endl;

    createInterface();
    return 0;
}
