#include "../../include/core/TpsDisplay.h"

TpsDisplay::TpsDisplay(int currentTps, int wantedTps, sf::Font font, sf::Vector2f viewScale) {
    this->font = font;
    this->viewScale = viewScale;
    this->currentTps = currentTps;
    this->wantedTps = wantedTps;
}

void TpsDisplay::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    sf::Text tpsText;
    tpsText.setString("TPS : ");
    tpsText.setFont(this->font);
    tpsText.setScale(this->viewScale.x, this->viewScale.y);
    tpsText.setPosition(32 * this->viewScale.x, 32 * this->viewScale.y);
    tpsText.setCharacterSize(64);
    tpsText.setFillColor(sf::Color::White);

    target.draw(tpsText, states);

    sf::Text tpsValueText;
    tpsValueText.setString(to_string(currentTps));
    tpsValueText.setFont(this->font);
    tpsValueText.setScale(this->viewScale.x, this->viewScale.y);
    tpsValueText.setPosition(32 * 6.5f * this->viewScale.x, 32 * this->viewScale.y);
    tpsValueText.setCharacterSize(64);
    tpsValueText.setFillColor(getTpsColor());

    target.draw(tpsValueText, states);

}

sf::Color TpsDisplay::getTpsColor() const {
    float percent = currentTps / wantedTps;

    if (percent < .3) {
        return sf::Color::Red;
    } else if (percent < .5) {
        //Dark Orange
        return {255, 140, 0, 255};
    } else if (percent < .75) {
        //Light Orange
        return {255, 165, 0, 255};
    } else if (percent < .9) {
        //Oranged green
        return {102, 204, 0, 255};
    } else {
        //Green
        return {0, 204, 0, 255};
    }
}
