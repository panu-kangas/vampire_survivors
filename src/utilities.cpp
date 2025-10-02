#include <SFML/Graphics.hpp>

void drawText(sf::RenderTarget &target, sf::Font font, std::string text)
{
	sf::Text startText;
	startText.setFont(font);
	startText.setString(text);
	startText.setFillColor(sf::Color::White);
	startText.setPosition(80.0f, 80.0f);
	startText.setStyle(sf::Text::Bold);
	target.draw(startText);
}