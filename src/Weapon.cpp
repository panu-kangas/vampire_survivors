#include "Weapon.h"
#include "Player.h"

#include <iostream>

Weapon::Weapon(std::string name, std::string upgradeName, Player* playerPtr) : Rectangle(sf::Vector2f(0, 0))
{
    setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setColor(sf::Color::Blue);

	m_name = name;
	m_upgradeName = upgradeName;
	m_playerPtr = playerPtr;
	m_pUpgradeValue = &m_weaponLength;
	m_cooldownClock.restart();
}

void Weapon::setActive(bool isActive)
{
	if (isActive && m_cooldownClock.getElapsedTime().asSeconds() < WeaponAttackCooldown)
		return ;
	
    m_isActive = isActive;
    if (isActive)
    {
		eDirection playerDir = m_playerPtr->getDirection();
		if (playerDir == LEFT || playerDir == RIGHT)
        	setSize(sf::Vector2f(m_weaponLength, WeaponHeight));
		else
			setSize(sf::Vector2f(WeaponHeight, m_weaponLength));

		m_weaponDir = playerDir;
        m_timer = WeaponActiveTime;
		m_cooldownClock.restart();
    }
    else
    {
        setSize(sf::Vector2f(0.0f, 0.0f));
        m_timer = 0.0f;
    }
}

void Weapon::handleUpgrade(float newUpgradeValue, int newUpgradeLevel)
{
	*m_pUpgradeValue = newUpgradeValue;
	m_upgradeLevel = newUpgradeLevel;
}

void Weapon::resetUpgrades()
{
	m_upgradeLevel = 1;
	*m_pUpgradeValue = WeaponWidth;
}


void Weapon::update(float deltaTime)
{
	if (m_weaponDir == LEFT || m_weaponDir == RIGHT)
	{
		setPosition(sf::Vector2f(
			m_playerPtr->getCenter().x - (m_weaponDir == LEFT ? getSize().x : 0.0f),
			m_playerPtr->getCenter().y - getSize().y / 2.0f));
	}
	else
	{
		setPosition(sf::Vector2f(
			m_playerPtr->getCenter().x - getSize().x / 2,
			m_playerPtr->getCenter().y - (m_weaponDir == UP ? getSize().y : 0.0f)));
	}


    if (m_isActive)
    {
        m_timer -= deltaTime;
        if (m_timer <= 0.0f)
        {
            setActive(false);
        }
    }
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape graphicsRect(getSize());
    graphicsRect.setFillColor(getColor());
    graphicsRect.setPosition(getPosition());
    target.draw(graphicsRect);
}

bool Weapon::checkCollision(Rectangle* obj)
{
	if (collidesWith(obj) && isActive())
		return true;

	return false;
}
