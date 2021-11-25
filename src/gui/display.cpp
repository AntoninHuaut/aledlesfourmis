#include "../../header/gui/display.h"

void display_cell(sf::RenderWindow *window, BoardCell *cell, sf::Texture texture) {

    if (cell->getBoardCellType() != BasicCellType)
        return;

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(sprite.getTexture()->getSize())));

    sprite.setPosition(cell->getPosLength() * 16, cell->getPosHeight() * 16);
    window->draw(sprite);

}