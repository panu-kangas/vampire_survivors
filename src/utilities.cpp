#include "utilities.hpp"

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
	textToDraw.setFillColor(sf::Color::Red);
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
	textToDraw.setPosition(xPos, ScreenHeight / 2);
	target.draw(textToDraw);
}