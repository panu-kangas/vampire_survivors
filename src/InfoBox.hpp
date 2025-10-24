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
	void initInfoBox(std::vector<std::string> texts, float fontSize, sf::Color bgColor);

	void setPosition(sf::Vector2f position) { m_position = position; };
	void setText(std::vector<std::string> texts);
	void setSize(sf::Vector2f newSize) { m_size = newSize; };
	void centerText() { m_isTextCentered = true; };
//	void setFontSize(float fontSize) { m_fontSize = fontSize; };
//	void setColor(sf::Color color) { m_bgColor = color; };
//	void setIcons(std::vector<sf::Sprite> icons);

	sf::Vector2f getSize() { return m_size; };
	sf::Vector2f getPosition() { return m_position; };
	sf::Color getColor() { return m_bgColor; };
	float getLineHeight() { return m_lineHeight; };
	bool isActive() { return m_isActive; };
	void changeActiveStatus() { m_isActive = !m_isActive; };

	private:

	Game* m_pGame = nullptr;
	std::vector<std::string> m_textVec;
//	std::vector<sf::Sprite> m_iconVec;
	float 	m_lineHeight = 30.f;
	float	m_fontSize = 30.f;
	bool 	m_isTextCentered = false;
	bool	m_isActive = false;
	sf::Vector2f m_size = {100.f, 100.f};
	sf::Vector2f m_position;
	sf::Font*	m_font;
	sf::Color	m_bgColor{sf::Color::Black};	
};