#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "DataStructs.hpp"

class Rectangle;

void drawText(sf::RenderTarget &target, sf::Font font, std::string text);
void drawHeaderText(sf::RenderTarget &target, sf::Font font, std::string text);
void drawCenteredText(sf::RenderTarget &target, sf::Font font, std::string text);
void drawBottomText(sf::RenderTarget &target, sf::Font font, std::string text);
bool isOutOfScreen(Rectangle& obj);
bool isVampireDataEmpty(VampireLevelData& vampireData);
std::string floatToString(float value, int precision = 2);
float getDistanceBetweenPoints(const sf::Vector2f& a, const sf::Vector2f& b);
