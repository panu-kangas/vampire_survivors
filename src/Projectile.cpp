#include "Projectile.hpp"
#include "utilities.hpp"

#include <iostream>

Projectile::Projectile(Game* gamePtr, sf::Vector2f size, sf::Vector2f position) : 
	Rectangle(size, position)
{
	m_position = position;
    m_sprite.setTexture(*gamePtr->getGreenVampireBulletTexture());
}

void Projectile::initProjectile(sf::Vector2f direction, float speed, sf::Color color)
{
	m_direction = direction;
	m_speed = speed;
	m_color = color;
	m_sprite.setColor(m_color);
}

void Projectile::update(float deltaTime)
{
	sf::Transformable::move(m_direction * m_speed * deltaTime);
	m_sprite.setPosition(getPosition());

	if (isOutOfScreen(*this))
	{
		m_isDestroyed = true;
	}
}

