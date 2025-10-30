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

	m_cooldownColumn.setSize(weaponAreaSize);
	m_cooldownColumn.setFillColor(m_readyColor);
	m_cooldownColumn.setPosition(position);

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
	float cooldownLimit = m_weapon->getCooldownLimit();
	float cooldownTime = m_weapon->getCooldownTime();

	if (cooldownTime < cooldownLimit)
	{
		if (m_cooldownColumn.getFillColor() == m_readyColor)
		{
			m_cooldownColumn.setFillColor(m_cooldownColor);
		}
		float columnLength = (cooldownTime / cooldownLimit) * m_box.getSize().x;
		m_cooldownColumn.setSize({columnLength, m_cooldownColumn.getSize().y});
	}
	else
	{
		if (m_cooldownColumn.getFillColor() == m_cooldownColor)
		{
			m_cooldownColumn.setFillColor(m_readyColor);
			m_cooldownColumn.setSize({m_box.getSize().x, m_cooldownColumn.getSize().y});
		}
	}

	if (m_weapon->isReadyToAttack() && m_box.getOutlineColor() == sf::Color::Red)
	{
		m_text.setFillColor(sf::Color::Green);
		m_box.setOutlineColor(sf::Color::Green);
	}
	else if (!m_weapon->isReadyToAttack() && m_box.getOutlineColor() == sf::Color::Green)
	{
		m_text.setFillColor(sf::Color::Red);
		m_box.setOutlineColor(sf::Color::Red);
	}
}

void WeaponInfoRenderer::render(sf::RenderTarget& target)
{
	target.draw(m_box);
	target.draw(m_cooldownColumn);
	target.draw(m_text);
}