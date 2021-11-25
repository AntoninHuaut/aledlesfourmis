#include <iostream>
#include <ctime>
#include "../header/map/BoardCell.h"
#include "../header/map/BasicCell.h"
#include "../header/map/BoardGenerator.h"
#include <SFML/Graphics.hpp>
#include "../header/gui/GUIMain.h"

TextureCache *TextureCache::instance = nullptr;

using namespace std;

void createInterface(Board *board) {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Vector2f oldPos;
    bool moving = false;
    float zoom = 1;
    float currentZoom = zoom;

    sf::View simulationView = window.getDefaultView();

    window.setView(simulationView);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    // Mouse button is pressed, get the position and set moving as active
                    if (event.mouseButton.button == 0) {
                        moving = true;
                        oldPos = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    // Mouse button is released, no longer move
                    if (event.mouseButton.button == 0) {
                        moving = false;
                    }
                    break;
                case sf::Event::MouseMoved: {
                    // Ignore mouse movement unless a button is pressed (see above)
                    if (!moving)
                        break;
                    // Determine the new position in world coordinates
                    const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));
                    // Determine how the cursor has moved
                    // Swap these to invert the movement direction
                    const sf::Vector2f deltaPos = oldPos - newPos;

                    // Move our view accordingly and update the window
                    simulationView.setCenter(simulationView.getCenter() + deltaPos);
                    window.setView(simulationView);

                    // Save the new position as the old one
                    // We're recalculating this, since we've changed the view
                    oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    break;
                }
                case sf::Event::MouseWheelScrolled:
                    // Ignore the mouse wheel unless we're not moving
                    //if (moving)
                    //    break;

                    // Determine the scroll direction and adjust the zoom level
                    // Again, you can swap these to invert the direction
                    if (event.mouseWheelScroll.delta <= -1)
                        zoom = std::min(2.f, zoom + .1f);
                    else if (event.mouseWheelScroll.delta >= 1)
                        zoom = std::max(.5f, zoom - .1f);

                    // Update our view
                    if (currentZoom != zoom) {

                        const sf::Vector2f newPos = window.mapPixelToCoords(
                                sf::Vector2i(sf::Mouse::getPosition(window)));
                        simulationView.setSize(window.getDefaultView().getSize()); // Reset the size
                        simulationView.zoom(zoom); // Apply the zoom level (this transforms the view)

                        currentZoom = zoom;
                    }


                    window.setView(simulationView);
                    break;

            }

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear();

        BoardCell ***cells = board->getCells();

        //display_cell(&window, cells[0][0]);
        //display_cell(&window, cells[0][1]);

        for (int i = 0; i < Config::HEIGHT; i++) {
            for (int j = 0; j < Config::LENGTH; j++) {

                //display_cell(&window, cells[i][j]);

            }
        }

        window.display();
    }
}

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)

    auto *test = BoardGenerator::generateBoard();

//    BoardCell *cell = new BasicCell(5);
//    auto *antQueen = new Queen();
//
//    antQueen->setCell(cell);
//    antQueen->tick();
//    std::cout << antQueen->getCurrentCell()->getMaxAntOnCell() << std::endl;

    //createInterface(test);

    auto *gui = new GUIMain(test);

    gui->start();

    return 0;
}
