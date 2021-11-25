#include "../../header/gui/GUIMain.h"

void renderingThread(threadData data) {
    data.window->setActive(true);
    data.window->setFramerateLimit(140);
    data.board->render();

    // Render loop
    while (data.window->isOpen()) {
        data.window->clear();
        data.window->draw(*(data.board));
        data.window->display();
    }
}

void GUIMain::preventOutOfBorder(sf::RenderWindow *window, sf::View *simulationView,
                                 float zoom, sf::Vector2f *deltaPos) {
    float tileSize = Config::get()->getTileSize();
    float marginOutOfBorder = Config::get()->getMarginOutOfBorder();
    float mapLengthX = tileSize * Config::get()->getLength(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    float mapHeightY = tileSize * Config::get()->getHeight(); // NOLINT(cppcoreguidelines-narrowing-conversions)

    sf::Vector2f newCenterPos = {simulationView->getCenter().x + deltaPos->x,
                                 simulationView->getCenter().y + deltaPos->y};

    newCenterPos.x = max(newCenterPos.x, (simulationView->getSize().x / 2) - (marginOutOfBorder * zoom));
    newCenterPos.y = max(newCenterPos.y, (simulationView->getSize().y / 2) - (marginOutOfBorder * zoom));

    newCenterPos.x = min(newCenterPos.x, (mapLengthX - simulationView->getSize().x / 2) + marginOutOfBorder * zoom);
    newCenterPos.y = min(newCenterPos.y, (mapHeightY - simulationView->getSize().y / 2) + marginOutOfBorder * zoom);

    simulationView->setCenter(newCenterPos);
    window->setView(*simulationView);
}

int runUI(Board *board) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ant Simulation");

    // Disabling OpenGL
    window.setActive(false);

    // Launching draw thread
    threadData data;
    data.board = board;
    data.window = &window;

    sf::Thread thread(&renderingThread, data);
    thread.launch();

    sf::Vector2f oldPos;
    bool moving = false;
    float zoom = 1;
    float currentZoom = zoom;

    sf::View simulationView = window.getDefaultView();

    // Event loop
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
                        cout << sf::Mouse::getPosition(window).x << endl;
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
                    if (!moving) break;

                    // Determine the new position in world coordinates
                    const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));

                    sf::Vector2f deltaPos = oldPos - newPos;
                    GUIMain::preventOutOfBorder(&window, &simulationView, zoom, &deltaPos);

                    // Save the new position as the old one
                    // We're recalculating this, since we've changed the view
                    oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    break;
                }
                case sf::Event::MouseWheelScrolled:
                    // Determine the scroll direction and adjust the zoom level
                    // Again, you can swap these to invert the direction
                    if (event.mouseWheelScroll.delta <= -1) {
                        zoom = std::min(10.f, zoom + 1.f);
                    } else if (event.mouseWheelScroll.delta >= 1) {
                        zoom = std::max(.5f, zoom - 1.f);
                    }

                    // Update our view
                    if (currentZoom != zoom) {
                        simulationView.setSize(window.getDefaultView().getSize()); // Reset the size
                        simulationView.zoom(zoom); // Apply the zoom level (this transforms the view)

                        currentZoom = zoom;
                    }

                    window.setView(simulationView);

                    sf::Vector2f deltaPos = {0, 0};
                    GUIMain::preventOutOfBorder(&window, &simulationView, zoom, &deltaPos);
                    break;
            }

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                // Udate the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
    }

    return 0;
}

int GUIMain::start() {
    return runUI(this->board);
}
