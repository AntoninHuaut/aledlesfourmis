#include "../../header/gui/display.h"

void display_cell (sf::RenderWindow *window) {

    sf::Texture texture;
    if (!texture.loadFromFile("./assets/tileset.png", sf::IntRect(10, 10, 320, 320)))
    {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(sprite.getTexture()->getSize())));

    window->draw(sprite);

}