#pragma once

#include "Rectangle.h"
#include "Constants.h"

class Player;

class Weapon : public Rectangle
{
public:

    Weapon(std::string name);
    virtual ~Weapon() {}

	// temp solution for fixing m_pUpgradeValue with std::vector push backs
	Weapon(const Weapon& other) : Rectangle(other) { m_pUpgradeValue = &m_weaponLength; };

    virtual void setActive(bool isActive);
    bool isActive() { return m_isActive; };
	
    virtual void update(float deltaTime, Player* playerPtr);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void handleUpgrade(float newUpgradeValue, int newUpgradeLevel);
	void resetUpgrades();

	float getWeaponLength() { return m_weaponLength; };
	void setWeaponLength(float newLength) { m_weaponLength = newLength; };
	float* getUpgradeValue() { return m_pUpgradeValue; };
	int getUpgradeLevel() { return m_upgradeLevel; };
	float getUpgradeScale() { return m_upgradeScale; };
	std::string getName() { return m_name; };

protected:

	bool m_isActive = false;
	float m_timer = 0.0f;
	float* m_pUpgradeValue;
	float m_upgradeScale = 15.f;
	int m_upgradeLevel = 1;
	std::string m_name;

private:

	float m_weaponLength = WeaponWidth;

};