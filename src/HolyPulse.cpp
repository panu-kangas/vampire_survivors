#include "HolyPulse.hpp"

#include <iostream>

HolyPulse::HolyPulse(std::string name) : Weapon(name)
{
	m_name = name;
	m_upgradeScale = 10.f;
	setPosition({200, 200});

}

void HolyPulse::update(float deltaTime)
{

}

void HolyPulse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape circle(m_radius);
    circle.setPosition(getPosition());

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(5);

	target.draw(circle);
}