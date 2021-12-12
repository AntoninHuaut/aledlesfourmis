#ifndef ANT_TPSDISPLAY_H
#define ANT_TPSDISPLAY_H

#include <SFML/Graphics.hpp>

using namespace std;

class TpsDisplay : public sf::Drawable, public sf::Transformable {

    sf::Font font;
    sf::Vector2f viewScale;

    int currentTps;
    int wantedTps;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Color getTpsColor() const;

public:

    explicit TpsDisplay(int currentTps, int wantedTps, sf::Font font, sf::Vector2f viewScale);

};


#endif
