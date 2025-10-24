#include "HolyPulse.hpp"
#include "Player.h"
#include "utilities.hpp"

#include <iostream>

HolyPulse::HolyPulse(std::string name) : Weapon(name)
{
	m_name = name;
	m_upgradeScale = 10.f;
	m_pUpgradeValue = &m_radius;
	m_cooldownTime = HolyPulseCooldownTime;

	setOrigin(sf::Vector2f(0.0f, 0.0f));

	m_circle.setRadius(m_radius);
	m_circle.setFillColor(sf::Color::Transparent);
    m_circle.setOutlineColor(sf::Color::White);
    m_circle.setOutlineThickness(5);
	m_circle.setOrigin(m_radius, m_radius);

	m_cooldownClock.restart();
}

void HolyPulse::update(float deltaTime, Player* playerPtr)
{
	sf::Vector2f newPos{playerPtr->getCenter().x, playerPtr->getCenter().y};

	setPosition(newPos);
	m_circle.setPosition(newPos);

	if (m_isActive)
	{
		if (!m_isPulseStarted)
		{
			m_isPulseStarted = true;
			m_timer = 0.f;
			m_circle.setRadius(0.0f);
		}

		m_timer += deltaTime;

		float t = m_timer / HolyPulseAnimationTime;
		if (t > 1.0f)
		{
			t = 1.0f;
			m_isActive = false;
			m_isPulseStarted = false;
		}

		float tempRadius = m_radius * t;
		m_circle.setOrigin(tempRadius, tempRadius);
		m_circle.setRadius(tempRadius);
	}
}

void HolyPulse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_isActive)
		target.draw(m_circle);
}

void HolyPulse::setActive(bool isActive)
{
	if (isActive && m_cooldownClock.getElapsedTime().asSeconds() < m_cooldownTime)
		return ;

	m_isActive = isActive;

	if (!m_isActive)
	{
		m_isPulseStarted = false;
		m_circle.setRadius(0.0f);
	}
	else
	{
		m_cooldownClock.restart();
	}
}

bool HolyPulse::checkCollision(Rectangle* obj)
{
	if (getDistanceBetweenPoints(obj->getCenter(), getCenter()) < m_circle.getRadius() + 15.f && isActive())
		return true;

	return false;
}

void HolyPulse::resetUpgrades()
{
	m_upgradeLevel = 1;
	*m_pUpgradeValue = HolyPulseRadius;
}
