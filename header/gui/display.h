#ifndef ANT_DISPLAY_H
#define ANT_DISPLAY_H

#include <SFML/Graphics.hpp>
#include "../map/BoardCell.h"
#include "UISprite.h"
#include "TextureCache.h"

void display_cell(sf::RenderWindow *window, BoardCell *cell, sf::Texture texture);

#endif
