#include "WeaponInfoRenderer.hpp"
#include "Constants.h"

WeaponInfoRenderer::WeaponInfoRenderer(Game* gamePtr, Weapon* weapon, sf::Vector2f position) :
	m_pGame(gamePtr),
	m_weapon(weapon)
{
	m_box.setSize(weaponAreaSize);
	m_box.setFillColor(sf::Color(242, 134, 39, 200));
	m_box.setOutlineThickness(3.0f);
	m_box.setOutlineColor(sf::Color::Green);
	m_box.setPosition(position);

	m_text.setFont(*m_pGame->getFont());
	m_text.setCharacterSize(23.f);
	m_text.setString(weapon->getName());
	m_text.setFillColor(sf::Color::Green);
	float textX = m_box.getPosition().x + m_box.getSize().x / 2 - m_text.getLocalBounds().width / 2;
	float textY = m_box.getPosition().y + 10.f;
	m_text.setPosition({textX, textY});
}

void WeaponInfoRenderer::update(float deltaTime)
{
	if (m_weapon->isReadyToAttack() && m_text.getFillColor() == sf::Color::Red)
	{
		m_text.setFillColor(sf::Color::Green);
		m_box.setOutlineColor(sf::Color::Green);
	}
	else if (!m_weapon->isReadyToAttack() && m_text.getFillColor() == sf::Color::Green)
	{
		m_text.setFillColor(sf::Color::Red);
		m_box.setOutlineColor(sf::Color::Red);
	}
}

void WeaponInfoRenderer::render(sf::RenderTarget& target)
{
	target.draw(m_box);
	target.draw(m_text);
}