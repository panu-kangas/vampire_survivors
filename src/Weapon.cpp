#include "Weapon.h"

Weapon::Weapon(std::string name) : Rectangle(sf::Vector2f(0, 0))
{
    setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setColor(sf::Color::Blue);

	m_name = name;
	m_pUpgradeValue = &m_weaponLength;
	m_upgradeScale = 20.f;
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


void Weapon::update(float deltaTime)
{
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