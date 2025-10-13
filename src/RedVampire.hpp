#pragma once

#include "Vampire.h"

class Game;

class RedVampire : public Vampire
{

public:

	RedVampire() = delete;
	RedVampire(Game* game, sf::Vector2f position);
	virtual ~RedVampire() {};
	
	bool update(float deltaTime) override;

private:

	void getNewDirection();
	void handleBlinking();

	sf::Clock m_dirChangeTimer;
	sf::Clock m_stopTimer;
	sf::Clock m_blinkTimer;
	// Add "Rampage timer" here; Red Vampires will target player after certain time has passed
	
	sf::Vector2f m_curDir;
  
};
