#pragma once

#include <string> // is this needed?
#include <vector>
#include <SFML/Graphics.hpp>

#include "DataStructs.hpp"

class Game;

class VampireInfoBox
{
	public:

	VampireInfoBox() = delete;
	VampireInfoBox(Game* gamePtr, VampireLevelData& vampireData);
	~VampireInfoBox() = default;
	
	void render(sf::RenderTarget& target, sf::RenderStates& states) const;
	void update(VampireLevelData& vampireData);

	sf::Vector2f getSize() { return m_size; };
	sf::Vector2f getPosition() { return m_position; };

	private:

	Game* m_pGame = nullptr;
	bool m_firstHeader = true;
	sf::Text m_headerText;
	std::vector<sf::Sprite> m_iconVec; // is vector the best solution here....?
	std::vector<sf::Text> m_vampireCountTextVec;
	std::vector<unsigned> m_vampireCountVec;
	float	m_fontSize = 25.f;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Font*	m_font;
	sf::Color	m_bgColor{sf::Color(242, 134, 39, 200)};	
};