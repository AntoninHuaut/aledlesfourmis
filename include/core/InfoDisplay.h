#ifndef ANT_INFODISPLAY_H
#define ANT_INFODISPLAY_H

#include <SFML/Graphics.hpp>

using namespace std;

class InfoDisplay : public sf::Drawable {

    sf::VertexArray *icon;
    sf::Font font;
    string text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:

    explicit InfoDisplay(string text, int tileNumber, sf::Texture tileSet, sf::Font font);

};


#endif
