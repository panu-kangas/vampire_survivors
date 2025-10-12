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
	m_sprite.setScale(2.3f, 2.3f);

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

	/**
	 * NOTE! 
	 * Update could not be overridden, instead just make a "new direction" function
	 * that is then overridden by RedVampire.
	 * This way we have the collision logic as common but moving patterns separate
	 */

	if (m_isKilled)
        return false;
	
    Player* pPlayer = m_pGame->getPlayer();

    if (collidesWith(pPlayer->getWeapon()))
    {
        setIsKilled(true);
        return true;
    }

    if (collidesWith(pPlayer))
	{
        pPlayer->takeDamage();
		return false;
	}

	
	if (m_dirChangeTimer.getElapsedTime().asSeconds() > RedVampireDirChangeCooldown)
	{
		getNewDirection();
		m_dirChangeTimer.restart();
	}

    sf::Transformable::move(m_curDir * RedVampireSpeed * deltaTime);
    m_sprite.setPosition(getPosition());

	return false;
}
