#include "../../include/core/InfoDisplay.h"
#include "../../include/Config.h"

InfoDisplay::InfoDisplay(string text, int tileNumber, sf::Texture tileSet, sf::Font font) {

    this->text = text;
    this->font = font;
    this->tileSet = tileSet;

    this->icon = new sf::VertexArray(sf::Quads, 4);

    int tileSize = Config::get()->getTileSize();

    int tu = (int) (tileNumber % (tileSet.getSize().x / tileSize));
    int tv = (int) (tileNumber / (tileSet.getSize().x / tileSize));

    (*icon)[0].position = sf::Vector2f(sf::Vector2i(0, 0));
    (*icon)[1].position = sf::Vector2f(sf::Vector2i(5 * tileSize, 0));
    (*icon)[2].position = sf::Vector2f(sf::Vector2i(5 * tileSize, 5 * tileSize));
    (*icon)[3].position = sf::Vector2f(sf::Vector2i(0, 5 * tileSize));

    // define its 4 texture coordinates
    (*icon)[0].texCoords = sf::Vector2f(sf::Vector2i(tu * tileSize, tv * tileSize));
    (*icon)[1].texCoords = sf::Vector2f(sf::Vector2i((tu + 1) * tileSize, tv * tileSize));
    (*icon)[2].texCoords = sf::Vector2f(sf::Vector2i((tu + 1) * tileSize, (tv + 1) * tileSize));
    (*icon)[3].texCoords = sf::Vector2f(sf::Vector2i(tu * tileSize, (tv + 1) * tileSize));

}

void InfoDisplay::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    states.texture = &tileSet;
    target.draw(*this->icon, states);

    sf::Text textToDraw;
    textToDraw.setString(this->text);
    textToDraw.setFont(this->font);
    textToDraw.setScale(1, 1);
    textToDraw.setPosition(32*5, 32);
    textToDraw.setCharacterSize(64);
    textToDraw.setFillColor(sf::Color::White);

    target.draw(textToDraw, states);

}
