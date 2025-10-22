#include "GreenVampire.hpp"
#include "utilities.hpp"
#include "MathUtils.h"
#include "Player.h"
#include "Game.h"

#include <iostream>

GreenVampire::GreenVampire(Game* game, sf::Vector2f position) : 
	Vampire(game, position)
{
	m_sprite.setColor(sf::Color::Green);
	m_sprite.setScale(2.3f, 2.3f);

	m_dirChangeTimer.restart();
	m_travelTimer.restart();
	m_shootTimer.restart();

	getNewDirection();
}


void GreenVampire::getNewDirection()
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

void GreenVampire::shoot(sf::Vector2f direction)
{
	Projectile tempProj(m_pGame, {GreenVampireBulletSize, GreenVampireBulletSize}, this->getPosition());
	tempProj.initProjectile(direction, GreenVampireBulletSpeed, sf::Color::Black);

	m_pGame->addNewProjectile(tempProj);
}

void GreenVampire::handleShooting()
{
	if (!m_isShooting)
		return ;
	
	float shootSequenceTime = m_shootTimer.getElapsedTime().asSeconds();
	float midSequence = GreenVampireShootTime / 2;

	if (shootSequenceTime < GreenVampireShootTime && shootSequenceTime > midSequence && !m_hasShot)
	{
		sf::Vector2f playerCenter = m_pGame->getPlayer()->getCenter();
		sf::Vector2f projectileDir = VecNormalized(playerCenter - getCenter());
		this->shoot(projectileDir);
		m_hasShot = true;
	}
	else if (shootSequenceTime > GreenVampireShootTime)
	{
		m_isShooting = false;
		m_hasShot = false;
		m_travelTimer.restart();
	}
}

bool  GreenVampire::update(float deltaTime)
{
	if (m_isKilled)
        return false;
	
    Player* pPlayer = m_pGame->getPlayer();

	// Separate collisions to own function...?

    if (checkWeaponHits(pPlayer))
    {
        setIsKilled(true);
        return true;
    }

    if (collidesWith(pPlayer))
	{
        pPlayer->takeDamage();
		return false;
	}

	if (m_dirChangeTimer.getElapsedTime().asSeconds() > GreenVampireDirChangeCooldown)
	{
		getNewDirection();
		m_dirChangeTimer.restart();
	}

	if (m_travelTimer.getElapsedTime().asSeconds() < GreenVampireTravelTime)
	{
		sf::Transformable::move(m_curDir * GreemVampireSpeed * deltaTime);
		m_sprite.setPosition(getPosition());
	}
	else if (!m_isShooting)
	{
		m_isShooting = true;
		m_shootTimer.restart();
	}
	
	this->handleShooting();

	return false;
}

void GreenVampire::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
