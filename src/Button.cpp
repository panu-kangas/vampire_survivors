#include "Button.hpp"
#include "Game.h"

Button::Button(Game* gamePtr) : m_pGame(gamePtr)
{
	m_font = m_pGame->getFont();
}

void Button::initButton(std::string text, sf::Color bgColor)
{
	m_text.setFont(*m_font);
    m_text.setCharacterSize(m_fontSize);
    m_text.setFillColor(sf::Color::White);
	m_text.setString(text);

	sf::FloatRect bounds = m_text.getLocalBounds();
	m_text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	
	m_bgColor = bgColor;

	m_size.x = m_text.getLocalBounds().width + 20.f;
	m_size.y = m_text.getLocalBounds().height + 20.f;

}


void Button::handleInput(InputData& inputData)
{
	if (m_isActive && m_pGame->isEnterPressed())
	{
		m_isPressed = true;
	}

	// TEST
	if (inputData.m_space)
		m_isActive = !m_isActive;
}

void Button::update(float deltaTime)
{

}

void Button::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	// Draw background box
    sf::RectangleShape background(m_size);
    background.setPosition(m_position);
    background.setFillColor(m_bgColor);
	background.setOutlineColor(m_isActive ? sf::Color::White : sf::Color::Black);
	background.setOutlineThickness(m_isActive ? 4.f : 2.f);
    target.draw(background);

    if (!m_font)
        return;

	float textX = m_position.x + m_size.x / 2;
	float textY = m_position.y + m_size.y / 2;
	m_text.setPosition(textX, textY);
	target.draw(m_text);

}