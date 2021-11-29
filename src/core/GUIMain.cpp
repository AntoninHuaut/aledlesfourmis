#include "../../header/core/GUIMain.h"

void renderingThread(threadData data) {
    data.window->setActive(true);
    data.window->setVerticalSyncEnabled(true);
    data.board->calcRender();

    // Render loop
    while (data.window->isOpen()) {
        data.window->clear();
        data.window->draw(*(data.board));
        data.window->display();
    }

    data.board->setFinishGame(true);
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
    center();

    // Event loop
    while (window->isOpen()) {
        sf::Event event{};
        smoothOnKeyPressed();

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

void GUIMain::smoothOnKeyPressed() {
    float padding = 0.01f * zoom;
    float speedMultiplier = 2.5f;
    sf::Vector2f deltaPos = {0, 0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) center();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) deltaPos.x -= padding;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) deltaPos.x += padding;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) deltaPos.y -= padding;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) deltaPos.y += padding;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        deltaPos.x *= speedMultiplier;
        deltaPos.y *= speedMultiplier;
    }

    if (deltaPos.x != 0 || deltaPos.y != 0) {
        GUIMain::preventOutOfBorder(deltaPos);
    }
}

void GUIMain::center() {
    auto mapSize = getMapSize();
    float mapLengthX = mapSize.x;
    float mapHeightY = mapSize.y;

    sf::Vector2f newCenterPos = {mapLengthX / 2, mapHeightY / 2};

    simView.setCenter(newCenterPos);
    window->setView(simView);
}

void GUIMain::preventOutOfBorder(sf::Vector2f deltaPos) {
    auto mapSize = getMapSize();
    float mapLengthX = mapSize.x;
    float mapHeightY = mapSize.y;
    float marginOutOfBorder = Config::get()->getMarginOutOfBorder();

    sf::Vector2f newCenterPos = {simView.getCenter().x + deltaPos.x, simView.getCenter().y + deltaPos.y};

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
    GUIMain::preventOutOfBorder(deltaPos);

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
        zoom = std::min(5.625f, zoom + zoomPadding);
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
    GUIMain::preventOutOfBorder(deltaPos);
}

void GUIMain::onResized(sf::Event event) {
    GUIMain::letterBoxView((float) event.size.width, (float) event.size.height);

    sf::Vector2f deltaPos = {0, 0};
    GUIMain::preventOutOfBorder(deltaPos);

    window->setView(simView);
}

sf::Vector2f GUIMain::getMapSize() {
    int tileSize = Config::get()->getTileSize();
    float mapLengthX = tileSize * Config::get()->getLength(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    float mapHeightY = tileSize * Config::get()->getHeight(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    return {mapLengthX, mapHeightY};
}
