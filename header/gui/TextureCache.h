#ifndef ANT_TEXTURECACHE_H
#define ANT_TEXTURECACHE_H


#include <iostream>
#include "UISprite.h"

using namespace std;

class TextureCache {

    static TextureCache *instance;
    map<SpriteEnum, sf::Texture> textures;

    TextureCache() = default;

public:

    static TextureCache *getInstance() {
        if (instance == nullptr) {
            instance = new TextureCache();
        }
        return instance;
    }

    sf::Texture getTexture(SpriteEnum sprite) {

        if (textures.find(sprite) != textures.end()) {
            return textures[sprite];
        }

        cout << "ALED" << endl;
        UISprite *spriteData = UISprite::getSprite(sprite);

        sf::Texture texture;

        if (!texture.loadFromFile(spriteData->getFilePath(), spriteData->getInRect())) {
            // error...
        }

        free(spriteData);

        textures[sprite] = texture;
        return texture;
    }

};

#endif
