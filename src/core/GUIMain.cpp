#include "../../include/core/GUIMain.h"
#include "../../include/core/SimulationStats.h"

void renderingThread(threadData data) {
    data.window->setActive(true);
    data.window->setFramerateLimit(Config::get()->getMaxFps());

    data.mutex->lock();
    data.board->calcFloor();
    data.mutex->unlock();

    // Render loop
    while (data.window->isOpen()) {
        if (!data.game->isPause()) {
            data.mutex->lock();
            data.board->calcLayer();
            data.mutex->unlock();
        }

        data.window->clear();
        data.window->setView(*data.simView);
        data.window->draw(*(data.board));
        data.window->setView(*data.statView);
        data.window->draw(*data.stats);
        data.window->display();
    }

    data.board->setWindowClosed(true);
}

void GUIMain::runUI(sf::Mutex *mutex) {
    // Disabling OpenGL
    window->setActive(false);

    sf::Vector2<unsigned int> windowSize = window->getSize();

    //Top corner view to display stats
    sf::View statView(sf::FloatRect(0.f, 0.f, 1000.f, 600.f));
    statView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.5f));

    simView = window->getDefaultView();

    // Launching draw thread
    threadData data;
    data.game = game;
    data.board = board;
    data.window = window;
    data.mutex = mutex;
    data.statView = &statView;
    data.simView = &simView;
    data.stats = stats;

    sf::Thread thread(&renderingThread, data);
    thread.launch();


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
        oldPos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window)), simView);
    }
}

void GUIMain::smoothOnKeyPressed() {
    if (!window->hasFocus()) return;

    float padding = 0.01f * zoom;
    float speedMultiplier = 2.5f;
    sf::Vector2f deltaPos = {0, 0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) center();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!waitReleaseGameKey) {
            game->setPause(!game->isPause());
            waitReleaseGameKey = true;
        }
    } else {
        waitReleaseGameKey = false;
    }

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
    //window->setView(simView);
}

void GUIMain::preventOutOfBorder(sf::Vector2f deltaPos) {
    auto mapSize = getMapSize();
    float mapLengthX = mapSize.x;
    float mapHeightY = mapSize.y;
    float marginOutOfBorder = Config::get()->getMarginOutOfBorder();

    sf::View defaultView = simView;

    sf::Vector2f newCenterPos = {defaultView.getCenter().x + deltaPos.x, defaultView.getCenter().y + deltaPos.y};

    newCenterPos.x = max(newCenterPos.x, (defaultView.getSize().x / 2) - (marginOutOfBorder * zoom));
    newCenterPos.y = max(newCenterPos.y, (defaultView.getSize().y / 2) - (marginOutOfBorder * zoom));

    newCenterPos.x = min(newCenterPos.x, (mapLengthX - defaultView.getSize().x / 2) + marginOutOfBorder * zoom);
    newCenterPos.y = min(newCenterPos.y, (mapHeightY - defaultView.getSize().y / 2) + marginOutOfBorder * zoom);

    simView.setCenter(newCenterPos);
    //window->setView(simView);
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
    const sf::Vector2f newPos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window)), simView);

    sf::Vector2f deltaPos = oldPos - newPos;
    GUIMain::preventOutOfBorder(deltaPos);

    // Save the new position as the old one
    // We're recalculating this, since we've changed the simView
    oldPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y), simView);
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

    //window->setView(simView);

    sf::Vector2f deltaPos = {0, 0};
    GUIMain::preventOutOfBorder(deltaPos);
}

void GUIMain::onResized(sf::Event event) {
    GUIMain::letterBoxView((float) event.size.width, (float) event.size.height);

    sf::Vector2f deltaPos = {0, 0};
    GUIMain::preventOutOfBorder(deltaPos);

    //window->setView(simView);
}

sf::Vector2f GUIMain::getMapSize() {
    int tileSize = Config::get()->getTileSize();
    float mapLengthX = tileSize * Config::get()->getLength(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    float mapHeightY = tileSize * Config::get()->getHeight(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    return {mapLengthX, mapHeightY};
}
