#include "Weapon.h"
#include "Player.h"

Weapon::Weapon(std::string name) : Rectangle(sf::Vector2f(0, 0))
{
    setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setColor(sf::Color::Blue);

	m_name = name;
	m_pUpgradeValue = &m_weaponLength;
}

void Weapon::setActive(bool isActive)
{
    m_isActive = isActive;
    if (isActive)
    {
        setSize(sf::Vector2f(m_weaponLength, WeaponHeight));
        m_timer = WeaponActiveTime;
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


void Weapon::update(float deltaTime, Player* playerPtr)
{
	setPosition(sf::Vector2f(
		playerPtr->getCenter().x - (playerPtr->getFacingDirection() == LEFT ? getSize().x : 0.0f),
		playerPtr->getCenter().y - getSize().y / 2.0f));

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