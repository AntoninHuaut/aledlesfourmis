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

void GUIMain::runUI() {
    // Disabling OpenGL
    window->setActive(false);

    // Launching draw thread
    threadData data;
    data.board = board;
    data.window = window;

    sf::Thread thread(&renderingThread, data);
    thread.launch();

    simView = window->getDefaultView();

    // Event loop
    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    onClosed();
                    break;
                case sf::Event::MouseButtonPressed:
                    onMouseButtonPressed(event);
                    break;
                case sf::Event::MouseButtonReleased:
                    onMouseButtonReleased(event);
                    break;
                case sf::Event::MouseMoved:
                    onMouseMoved(event);
                    break;
                case sf::Event::MouseWheelScrolled:
                    onMouseWheelScrolled(event);
                    break;
                case sf::Event::Resized:
                    onResized(event);
                    break;
                default:
                    break;
            }
        }
    }
}

void GUIMain::onClosed() {
    window->close();
}

void GUIMain::onMouseButtonPressed(sf::Event event) {
    // Mouse button is pressed, get the position and set moving as active
    if (event.mouseButton.button == 0) {
        moving = true;
        oldPos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window)));
    }
}

void GUIMain::preventOutOfBorder(sf::Vector2f *deltaPos) {
    int tileSize = Config::get()->getTileSize();
    float marginOutOfBorder = Config::get()->getMarginOutOfBorder();
    float mapLengthX = tileSize * Config::get()->getLength(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    float mapHeightY = tileSize * Config::get()->getHeight(); // NOLINT(cppcoreguidelines-narrowing-conversions)

    sf::Vector2f newCenterPos = {simView.getCenter().x + deltaPos->x, simView.getCenter().y + deltaPos->y};

    newCenterPos.x = max(newCenterPos.x, (simView.getSize().x / 2) - (marginOutOfBorder * zoom));
    newCenterPos.y = max(newCenterPos.y, (simView.getSize().y / 2) - (marginOutOfBorder * zoom));

    newCenterPos.x = min(newCenterPos.x, (mapLengthX - simView.getSize().x / 2) + marginOutOfBorder * zoom);
    newCenterPos.y = min(newCenterPos.y, (mapHeightY - simView.getSize().y / 2) + marginOutOfBorder * zoom);

    simView.setCenter(newCenterPos);
    window->setView(simView);
}

void GUIMain::letterBoxView(float windowWidth, float windowHeight) {
    float windowRatio = windowWidth / windowHeight;
    float viewRatio = simView.getSize().x / (float) simView.getSize().y;
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

    simView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void GUIMain::onMouseButtonReleased(sf::Event event) {
    // Mouse button is released, no longer move
    if (event.mouseButton.button == 0) {
        moving = false;
    }
}

void GUIMain::onMouseMoved(sf::Event event) {
    // Ignore mouse movement unless a button is pressed (see above)
    if (!moving) return;

    // Determine the new position in world coordinates
    const sf::Vector2f newPos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window)));

    sf::Vector2f deltaPos = oldPos - newPos;
    GUIMain::preventOutOfBorder(&deltaPos);

    // Save the new position as the old one
    // We're recalculating this, since we've changed the simView
    oldPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
}

void GUIMain::onMouseWheelScrolled(sf::Event event) {
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
        simView.setSize(window->getDefaultView().getSize()); // Reset the size
        simView.zoom(zoom); // Apply the zoom level (this transforms the simView)

        currentZoom = zoom;
    }

    window->setView(simView);

    sf::Vector2f deltaPos = {0, 0};
    GUIMain::preventOutOfBorder(&deltaPos);
}

void GUIMain::onResized(sf::Event event) {
    GUIMain::letterBoxView((float) event.size.width, (float) event.size.height);

    sf::Vector2f deltaPos = {0, 0};
    GUIMain::preventOutOfBorder(&deltaPos);

    window->setView(simView);
}
