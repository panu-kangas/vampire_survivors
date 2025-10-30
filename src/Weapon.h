#pragma once

#include "Rectangle.h"
#include "Constants.h"
#include "Enums.hpp"

class Player;

class Weapon : public Rectangle
{
public:

    Weapon(std::string name, std::string upgradeName, Player* playerPtr);
    virtual ~Weapon() {}

	// temp solution for fixing m_pUpgradeValue with std::vector push backs
	Weapon(const Weapon& other) : Rectangle(other) { m_pUpgradeValue = &m_weaponLength; };

    virtual void setActive(bool isActive);
    bool isActive() { return m_isActive; };
	
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual bool checkCollision(Rectangle* obj);

	void handleUpgrade(float newUpgradeValue, int newUpgradeLevel);
	virtual void resetUpgrades();

	float getWeaponLength() { return m_weaponLength; };
	void setWeaponLength(float newLength) { m_weaponLength = newLength; };
	float* getUpgradeValue() { return m_pUpgradeValue; };
	int getUpgradeLevel() { return m_upgradeLevel; };
	float getUpgradeScale() { return m_upgradeScale; };
	bool isReadyToAttack() { return m_cooldownClock.getElapsedTime().asSeconds() > m_cooldownLimit; };
	float getCooldownLimit() { return m_cooldownLimit; };
	float getCooldownTime() { return m_cooldownClock.getElapsedTime().asSeconds(); };
	std::string getName() { return m_name; };
	std::string getUpgradeName() { return m_upgradeName; };


protected:

	bool m_isActive = false;
	float m_timer = 0.0f;
	float m_cooldownLimit = WeaponAttackCooldown;
	float* m_pUpgradeValue;
	float m_upgradeScale = 20.f;
	int m_upgradeLevel = 1;
	std::string m_name;
	std::string m_upgradeName;
	Player* m_playerPtr;
	eDirection m_weaponDir = LEFT;

	sf::Clock m_cooldownClock;

private:

	float m_weaponLength = WeaponWidth;

};