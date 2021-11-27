#include "../../header/gui/GUIMain.h"

void renderingThread(threadData data) {
    data.window->setActive(true);
    data.window->setFramerateLimit(Config::get()->getFpsMax());
    data.board->render();

    // Render loop
    while (data.window->isOpen()) {
        data.window->clear();
        data.window->draw(*(data.board));
        data.window->display();
    }
}

int runUI(Board *board) {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Ant Simulation");

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

    sf::View simView = window.getDefaultView();

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
                    GUIMain::preventOutOfBorder(&window, &simView, zoom, &deltaPos);

                    // Save the new position as the old one
                    // We're recalculating this, since we've changed the simView
                    oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    break;
                }
                case sf::Event::MouseWheelScrolled:
                    // Determine the scroll direction and adjust the zoom level
                    // Again, you can swap these to invert the direction

                    auto boardHeight = Config::get()->getHeightFloat();
                    auto boardLength = Config::get()->getLengthFloat();
                    float zoomPadding = (log(boardHeight) * log(boardLength)) / (log(201.f) * log(211.f));

                    if (event.mouseWheelScroll.delta <= -1) {
                        zoom = std::min(6.f, zoom + zoomPadding);
                    } else if (event.mouseWheelScroll.delta >= 1) {
                        zoom = std::max(.5f, zoom - zoomPadding);
                    }

                    // Update our simView
                    if (currentZoom != zoom) {
                        simView.setSize(window.getDefaultView().getSize()); // Reset the size
                        simView.zoom(zoom); // Apply the zoom level (this transforms the simView)

                        currentZoom = zoom;
                    }

                    window.setView(simView);

                    sf::Vector2f deltaPos = {0, 0};
                    GUIMain::preventOutOfBorder(&window, &simView, zoom, &deltaPos);
                    break;
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                simView = GUIMain::getLetterboxView(simView, (float) event.size.width, (float) event.size.height);

                sf::Vector2f deltaPos = {0, 0};
                GUIMain::preventOutOfBorder(&window, &simView, zoom, &deltaPos);

                window.setView(simView);
            }
        }
    }

    return 0;
}

int GUIMain::start() {
    return runUI(this->board);
}

void GUIMain::preventOutOfBorder(sf::RenderWindow *window, sf::View *simulationView,
                                 float zoom, sf::Vector2f *deltaPos) {
    int tileSize = Config::get()->getTileSize();
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

sf::View GUIMain::getLetterboxView(sf::View view, float windowWidth, float windowHeight) {
    float windowRatio = windowWidth / windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = windowRatio >= viewRatio;

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}