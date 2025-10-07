#include "utilities.hpp"
#include "Rectangle.h"
#include "Constants.h"

void drawText(sf::RenderTarget &target, sf::Font font, std::string text)
{
	sf::Text textToDraw;
	textToDraw.setFont(font);
	textToDraw.setString(text);
	textToDraw.setFillColor(sf::Color::White);
	textToDraw.setPosition(80.0f, 80.0f);
	textToDraw.setStyle(sf::Text::Bold);
	target.draw(textToDraw);
}

void drawHeaderText(sf::RenderTarget &target, sf::Font font, std::string text)
{
	sf::Text textToDraw;
	textToDraw.setFont(font);
	textToDraw.setString(text);
	textToDraw.setCharacterSize(100);
	textToDraw.setFillColor(sf::Color(242, 134, 39));
	textToDraw.setStyle(sf::Text::Bold);
	float xPos = ScreenWidth / 2 - textToDraw.getLocalBounds().width / 2;
	textToDraw.setPosition(xPos, 50.0f);
	target.draw(textToDraw);
}

void drawCenteredText(sf::RenderTarget &target, sf::Font font, std::string text)
{
	sf::Text textToDraw;
	textToDraw.setFont(font);
	textToDraw.setString(text);
	textToDraw.setCharacterSize(50);
	textToDraw.setFillColor(sf::Color::White);
	textToDraw.setStyle(sf::Text::Bold);
	float xPos = ScreenWidth / 2 - textToDraw.getLocalBounds().width / 2;
	textToDraw.setPosition(xPos, ScreenHeight * 0.4);
	target.draw(textToDraw);
}

void drawBottomText(sf::RenderTarget &target, sf::Font font, std::string text)
{
	sf::Text textToDraw;
	textToDraw.setFont(font);
	textToDraw.setString(text);
	textToDraw.setCharacterSize(50);
	textToDraw.setFillColor(sf::Color::White);
	textToDraw.setStyle(sf::Text::Bold);
	float xPos = ScreenWidth / 2 - textToDraw.getLocalBounds().width / 2;
	textToDraw.setPosition(xPos, ScreenHeight * 0.9);
	target.draw(textToDraw);
}

bool isOutOfScreen(Rectangle& obj)
{
	float x = obj.getPosition().x;
	float y = obj.getPosition().y;
	float width = obj.getSize().x;
	float height = obj.getSize().y;

	if (x < 0 - width || x > ScreenWidth || y < 0 - height || y > ScreenHeight)
		return true;

	return false;
}

bool isVampireDataEmpty(VampireLevelData& vampireData)
{
	if (vampireData.whiteVampireCount == 0 && vampireData.redVampireCount == 0
	&& vampireData.greenVampireCount == 0 && vampireData.bossVampireCount == 0)
	{
		return true;
	}
	return false;
}