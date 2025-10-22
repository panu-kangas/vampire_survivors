#include "HolyPulse.hpp"
#include "Player.h"

#include <iostream>

HolyPulse::HolyPulse(std::string name) : Weapon(name)
{
	m_name = name;
	m_upgradeScale = 10.f;
	setOrigin(sf::Vector2f(0.0f, 0.0f));

	m_circle.setRadius(m_radius);
	m_circle.setFillColor(sf::Color::Transparent);
    m_circle.setOutlineColor(sf::Color::White);
    m_circle.setOutlineThickness(5);

	m_circle.setOrigin(m_radius, m_radius);


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
			m_radius = 0.f;
		}

		m_timer += deltaTime;

		float t = m_timer / HolyPulseAnimationTime;
		if (t > 1.0f)
		{
			t = 1.0f;
			m_isActive = false;
			m_isPulseStarted = false;
		}

		m_radius = HolyPulseRadius * t;
		m_circle.setOrigin(m_radius, m_radius);
		m_circle.setRadius(m_radius);
	}
}

void HolyPulse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_isActive)
		target.draw(m_circle);
}

void HolyPulse::setActive(bool isActive)
{
	m_isActive = isActive;

	if (!m_isActive)
	{
		m_isPulseStarted = false;
		m_radius = 0.0f;
		m_circle.setRadius(m_radius);
	}
}
