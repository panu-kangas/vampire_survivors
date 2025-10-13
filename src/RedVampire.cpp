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
	m_stopTimer.restart();
	m_blinkTimer.restart();

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

	sf::Vector2f playerCenter = m_pGame->getPlayer()->getCenter();
    m_curDir = VecNormalized(playerCenter - getCenter());

}

void RedVampire::handleBlinking()
{
	if (m_blinkTimer.getElapsedTime().asSeconds() > RedVampireBlinkInterval)
	{
		sf::Color newColor = m_sprite.getColor() == sf::Color::Red ? sf::Color(247, 186, 186) : sf::Color::Red;
		m_sprite.setColor(newColor);
		m_blinkTimer.restart();
	}
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
		m_stopTimer.restart();
	}

	if (m_stopTimer.getElapsedTime().asSeconds() < RedVampireStopCooldown)
	{
		sf::Transformable::move(m_curDir * RedVampireSpeed * deltaTime);
		m_sprite.setPosition(getPosition());
	}

	float timeUntilNewDirection = RedVampireDirChangeCooldown - m_dirChangeTimer.getElapsedTime().asSeconds();
	if (timeUntilNewDirection < 1.f)
		handleBlinking();

	

	return false;
}
