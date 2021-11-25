#ifndef ANT_UISPRITE_H
#define ANT_UISPRITE_H

#include <cstring>
#include "SpriteEnum.h"

using namespace std;

class UISprite {

    string filePath;

    int xPosOnFile;
    int yPosOnFile;

    int xSize = 16;
    int ySize = 16;

public:

    UISprite(string filePath, int xPosOnFile, int yPosOnFile) {
        this->filePath = filePath;
        this->xPosOnFile = xPosOnFile;
        this->yPosOnFile = yPosOnFile;
    };

    string getFilePath() { return this->filePath; };

    int getXPosOnFile() { return this->xPosOnFile; };

    int getYPosOnFile() { return this->yPosOnFile; };

    int getXSize() { return this->xSize; };

    int getYSize() { return this->ySize; };

    sf::IntRect getInRect() { return sf::IntRect(xPosOnFile, yPosOnFile, xSize, ySize); };

    static UISprite *getSprite(SpriteEnum sprite) {
        switch (sprite) {

            case SpriteEnum::BASIC_FLOOR:
                return new UISprite("./assets/TilesetFloor.png", 0, 16 * 12);
                break;

            default:
                return new UISprite("", 0, 0);
                break;
        }
    }

};


#endif
