#include "../../header/gui/display.h"
#include "../../header/gui/UISprite.h"
#include "../../header/gui/SpriteEnum.h"

void display_cell(sf::RenderWindow *window) {

    sf::Texture texture;

    UISprite *spriteData = UISprite::getSprite(SpriteEnum::BASIC_FLOOR);

    if (!texture.loadFromFile(spriteData->getFilePath(), spriteData->getInRect())) {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(sprite.getTexture()->getSize())));

    free(spriteData);

    window->draw(sprite);

}