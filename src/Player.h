#pragma once

#include "Rectangle.h"
#include "Weapon.h"
#include "HolyPulse.hpp"
#include "Constants.h"
#include "InfoBox.hpp"

#include <memory>
#include <SFML/Audio.hpp>

struct InputData;
class Game;

enum eDirection
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum eAttackType
{
	LANCE,
	HOLY_PULSE
};

class Player : public Rectangle
{
public:
    Player(Game* pGame);
    virtual ~Player() {}
    
    bool initialise(bool isFullReset = false);
    void move(InputData inputData, float deltaTime);
    void attack(eAttackType attackType);
    void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }
	bool takeDamage();
	void handleBlinking();
	void upgradeSpeed(float newSpeed, int newUpgradeLevel) { m_speed = newSpeed; m_upgradeLevel = newUpgradeLevel; }; 

    std::vector<Weapon*>& getWeaponVec() { return m_weaponVec; };
	eDirection getFacingDirection() { return m_facingDirection; };
	float getSpeed() { return m_speed; };
	float getUpgradeScale() { return m_upgradeScale; };
	int	getHealth() { return m_health; };
	int getUpgradeLevel() { return m_upgradeLevel; };
	int& getSkillPoints() { return m_skillPoints; };

private:

    bool    m_isDead = false;
	bool	m_isVisible = true;
	float	m_attackCooldown = 0.0f;
	float 	m_speed = PlayerSpeed;
	float 	m_upgradeScale = 10.f;
	int 	m_upgradeLevel = 1;
	int		m_health = PlayerStartHealth;
	int 	m_skillPoints = PlayerStartSkillPoints;
	sf::Clock m_playerDamageClock;
	sf::Clock m_blinkTimer;
    eDirection m_direction = LEFT;
	eDirection m_facingDirection = LEFT;
    Game*   m_pGame;
	sf::Sound m_hitSound;
	sf::Sound m_takeDmgSound;

	Weapon m_lance;
	HolyPulse m_holyPulse;

	std::vector<Weapon*> m_weaponVec;
};
