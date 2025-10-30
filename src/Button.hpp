#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Enums.hpp"

class Game;

class Button
{
	public:

	Button() = delete;
	Button(Game* gamePtr, eButtonType type);
	virtual ~Button() = default;

	void handleInput(InputData& inputData);
	void update(float deltaTime);
    void render(sf::RenderTarget& target, sf::RenderStates& states);
	void initButton(std::string text, sf::Color bgColor, sf::Color darkBgColor);

	bool isActive() { return m_isActive; };
	bool isPressed();
	sf::Vector2f getSize() { return m_size; };
	eButtonType getType() { return m_type; };
	sf::Vector2f getPosition() { return m_position; };

	void setPosition(sf::Vector2f newPos) { m_position = newPos; };
	void setSize(sf::Vector2f newSize) { m_size = newSize; };
	void changeActiveStatus() { m_isActive = !m_isActive; };
	void updateFontSize(float newSize);

	private:

	bool m_isActive = false;
	bool m_isPressed = false;
	float m_fontSize = 25.f;

	eButtonType m_type;

	Game* m_pGame;
	sf::Font* m_font;
	sf::Text m_text;
	sf::Vector2f m_size = {100.f, 100.f};
	sf::Vector2f m_position = {0, 0};
	sf::Color m_bgColor = sf::Color::Red;
	sf::Clock m_pressClock;

	sf::Color m_darkBgColor;

};