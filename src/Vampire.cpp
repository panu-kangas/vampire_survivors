#include "Vampire.h"
#include "Constants.h"
#include "Game.h"
#include "Weapon.h"
#include "Player.h"
#include "MathUtils.h"
#include "utilities.hpp"
#include "Constants.h"

#include <iostream>

Vampire::Vampire(Game* game, sf::Vector2f position) :
    Rectangle(sf::Vector2f(VampireWidth, VampireHeight)),
    m_pGame(game)
{
    setPosition(position);
	m_initPosition = position;
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setIsKilled(false);

    m_sprite.setTexture(*m_pGame->getVampireTexture());
    m_sprite.setScale(2.0f, 2.0f);
}

bool Vampire::update(float deltaTime)
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

    sf::Vector2f playerCenter = pPlayer->getCenter();
    sf::Vector2f direction = VecNormalized(playerCenter - getCenter());
    direction *= VampireSpeed * deltaTime;
    sf::Transformable::move(direction);
    m_sprite.setPosition(getPosition());

	return false;
}

bool Vampire::startScreenUpdate(float deltaTime)
{
	sf::Vector2f curPos = getPosition();
    if (curPos.x < 0 - VampireWidth || curPos.x > ScreenWidth)
    {
        setIsKilled(true);
        return true;
    }

    sf::Vector2f direction;
	direction.x = m_initPosition.x <= 0 ? 1 : -1;
	direction.y = 0;

    direction *= VampireSpeed * deltaTime;
    sf::Transformable::move(direction);
    m_sprite.setPosition(getPosition());

	return false;
}