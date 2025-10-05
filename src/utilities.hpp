#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Rectangle;

void drawText(sf::RenderTarget &target, sf::Font font, std::string text);
void drawHeaderText(sf::RenderTarget &target, sf::Font font, std::string text);
void drawCenteredText(sf::RenderTarget &target, sf::Font font, std::string text);
bool isOutOfScreen(Rectangle& obj);

