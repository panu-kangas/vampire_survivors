#pragma once

#include "Vampire.h"
#include "Projectile.hpp"

class Game;
class Player;

class GreenVampire : public Vampire
{

public:

	GreenVampire() = delete;
	GreenVampire(Game* game, sf::Vector2f position);
	virtual ~GreenVampire() {};
	
	bool update(float deltaTime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
	
	void shoot(sf::Vector2f direction);
	void handleShooting();
	void getNewDirection();

	sf::Clock m_dirChangeTimer;
	sf::Clock m_travelTimer;
	sf::Clock m_shootTimer;
	
	sf::Vector2f m_curDir;

	bool m_isShooting = false;
	bool m_hasShot = false;
	
  
};