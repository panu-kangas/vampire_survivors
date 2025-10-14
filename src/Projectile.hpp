#pragma once

#include "Game.h"
#include "Rectangle.h"
#include "Constants.h"


class Projectile : public Rectangle
{
	public:

	Projectile() = delete;
	Projectile(Game* gamePtr, sf::Vector2f size, sf::Vector2f position);
	virtual ~Projectile() = default;

	void initProjectile(sf::Vector2f direction, float speed, sf::Color color);
	void update(float deltaTime);

	void setAsDestroyed() { m_isDestroyed = true; };
	bool isDestroyed() { return m_isDestroyed; };

	private:

	sf::Vector2f m_position;
	sf::Vector2f m_direction {0, 0};
	sf::Color 	m_color {sf::Color::Black};
	float 	m_speed = 10.f;
	bool m_isDestroyed = false;

};