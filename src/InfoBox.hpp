#pragma once

#include <string> // is this needed?
#include <vector>
#include <SFML/Graphics.hpp>

class Game;

class InfoBox
{
	public:

	InfoBox() = delete;
	InfoBox(Game* gamePtr);
	virtual ~InfoBox() = default;
	
	void render(sf::RenderTarget& target, sf::RenderStates& states) const;

	void setColor(sf::Color color) { m_bgColor = color; };
	void setPosition(sf::Vector2f position) { m_position = position; };
	void setFontSize(float fontSize) { m_fontSize = fontSize; };
	void setText(std::vector<std::string> texts);

	sf::Vector2f getSize() { return m_size; };

	private:

	Game* m_pGame = nullptr;
	std::vector<std::string> m_textVec;
	float 	m_lineHeight = 30.f;
	float	m_fontSize = 30.f;
	sf::Vector2f m_size = {100.f, 100.f};
	sf::Vector2f m_position;
	sf::Font*	m_font;
	sf::Color	m_bgColor{sf::Color::Black};	
};