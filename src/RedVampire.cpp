#include "RedVampire.hpp"
#include "Game.h"
#include "Constants.h"
#include "Player.h"
#include "MathUtils.h"
#include "utilities.hpp"

#include <iostream>

RedVampire::RedVampire(Game* game, sf::Vector2f position) : Vampire(game, position)
{
	m_sprite.setColor(sf::Color::Red);

	m_dirChangeTimer.restart();

	getNewDirection();
}

void RedVampire::getNewDirection()
{
	if (isOutOfScreen(*this))
	{
		sf::Vector2f newDir{0, 0};
		sf::Vector2f curPos = getPosition();

		if (curPos.x < 0)
			newDir.x = 1;
		else if (curPos.x > ScreenWidth)
			newDir.x = -1;

		if (curPos.y < 0)
			newDir.y = 1;
		else if (curPos.y > ScreenHeight)
			newDir.y = -1;

		m_curDir = VecNormalized(newDir);
		
		return ;
	}

	sf::Vector2f randomPos;
	randomPos.x = rand() % ScreenWidth;
    randomPos.y = rand() % ScreenHeight;

	m_curDir = VecNormalized(randomPos - getCenter());
}

bool RedVampire::update(float deltaTime)
{
	if (m_isKilled)
        return false;
	
    Player* pPlayer = m_pGame->getPlayer();

    if (collidesWith(pPlayer->getWeapon()))
    {
        setIsKilled(true);
        return true;
    }

    if (collidesWith(pPlayer))
        pPlayer->setIsDead(true);

	
	if (m_dirChangeTimer.getElapsedTime().asSeconds() > RedVampireDirChangeCooldown)
	{
		getNewDirection();
		m_dirChangeTimer.restart();
	}

	// std::cout << "Red vamp curDir: x = " << m_curDir.x << ", y = " << m_curDir.y << "/n";
	// std::cout << "DeltaTime: " << deltaTime << "\n";

    sf::Transformable::move(m_curDir * RedVampireSpeed * deltaTime);
    m_sprite.setPosition(getPosition());

	return false;
}
