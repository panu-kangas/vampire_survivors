#pragma once

#include "Rectangle.h"
#include "Constants.h"

class Weapon : public Rectangle
{
public:

    Weapon(std::string name);
    virtual ~Weapon() {}

    void setActive(bool isActive);
    void update(float deltaTime);
    bool isActive() { return m_isActive; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void handleUpgrade(float newUpgradeValue, int newUpgradeLevel);
	void resetUpgrades();

	float getWeaponLength() { return m_weaponLength; };
	void setWeaponLength(float newLength) { m_weaponLength = newLength; };
	float* getUpgradeValue() { return m_pUpgradeValue; };
	int getUpgradeLevel() { return m_upgradeLevel; };
	float getUpgradeScale() { return m_upgradeScale; };
	std::string getName() { return m_name; };

private:

    bool m_isActive = false;
    float m_timer = 0.0f;
	float m_weaponLength = WeaponWidth;
	float* m_pUpgradeValue;
	float m_upgradeScale;
	int m_upgradeLevel = 1;
	std::string m_name;

};