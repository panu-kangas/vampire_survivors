#include "Player.h"
#include "Weapon.h"
#include "InputHandler.h"
#include "Constants.h"
#include <vector>
#include "Game.h"

Player::Player(Game* pGame) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame),
    m_pWeapon(std::make_unique<Weapon>("Lance"))
{
    setOrigin(sf::Vector2f(0.0f, 0.0f));
	m_playerDamageClock.restart();
	m_blinkTimer.restart();
}

bool Player::initialise(bool isFullReset)
{
    m_sprite.setTexture(*m_pGame->getPlayerTexture());
    m_sprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
    m_sprite.setScale(3.5f, 3.5f);
	m_direction = LEFT;
	m_facingDirection = LEFT;
    setIsDead(false);
    setPosition(ScreenWidth / 2, ScreenHeight / 2);
    m_sprite.setPosition(getPosition());
	m_pWeapon->setActive(false);
	if (isFullReset)
	{
		m_health = PlayerStartHealth;
		m_pWeapon->resetUpgrades();
	}
    return true;
}

void Player::move(InputData inputData, float deltaTime)
{
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;
    
    xSpeed -= inputData.m_movingLeft * PlayerSpeed;
    xSpeed += inputData.m_movingRight * PlayerSpeed;
    xSpeed *= deltaTime;

    ySpeed -= inputData.m_movingUp * PlayerSpeed;
    ySpeed += inputData.m_movingDown * PlayerSpeed;
    ySpeed *= deltaTime;
    
    sf::Transformable::move(sf::Vector2f(xSpeed, ySpeed));
    setPosition(std::clamp(getPosition().x, 0.0f, (float)ScreenWidth - PlayerWidth), 
	std::clamp(getPosition().y, 0.0f, (float)ScreenHeight - PlayerHeight));

    if (inputData.m_movingLeft && !inputData.m_movingRight)
        m_direction = LEFT;
    else if (!inputData.m_movingLeft && inputData.m_movingRight)
        m_direction = RIGHT;
    else if (inputData.m_movingUp && !inputData.m_movingDown)
        m_direction = UP;
    else if (!inputData.m_movingUp && inputData.m_movingDown)
        m_direction = DOWN;
}

void Player::attack()
{
	if (m_attackCooldown <= 0.0f)
	{
    	m_pWeapon->setActive(true);
		m_attackCooldown = PlayerAttackCooldown;
		m_hitSound.setBuffer(*m_pGame->getPlayerAttackBuff());
		m_hitSound.play();
	}
}

void Player::handleBlinking()
{
	if (m_blinkTimer.getElapsedTime().asSeconds() < PlayerBlinkInterval)
		return ;

	m_isVisible = m_isVisible ? false : true;
	m_blinkTimer.restart();
}

void Player::update(float deltaTime)
{
    sf::Vector2f weaponSize = m_pWeapon->getSize();

    m_sprite.setPosition(getPosition());
	if (m_direction != m_facingDirection && (m_direction == LEFT || m_direction == RIGHT))
	{
		m_facingDirection = m_direction;
		if (m_facingDirection == LEFT)
		{
    		m_sprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
    		m_sprite.setScale(3.5f, 3.5f);
		}
		else
		{
			m_sprite.setOrigin(m_sprite.getLocalBounds().width, 0);
			m_sprite.setScale(-3.5f, 3.5f);
		}
	}

	if (m_playerDamageClock.getElapsedTime().asSeconds() < PlayerDamageCooldown)
		handleBlinking();
	else if (!m_isVisible)
		m_isVisible = true;

    m_pWeapon->setPosition(sf::Vector2f(
        getCenter().x - (m_facingDirection == LEFT ? weaponSize.x : 0.0f),
        getCenter().y - weaponSize.y / 2.0f));
    m_pWeapon->update(deltaTime);
	if (m_attackCooldown > 0)
		m_attackCooldown -= deltaTime;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_isVisible)
	{
		Rectangle::draw(target, states);
		m_pWeapon->draw(target, states);
	}
}

// Return true = player took a hit, return false = player was invulnerable
bool Player::takeDamage()
{
	if (m_playerDamageClock.getElapsedTime().asSeconds() > PlayerDamageCooldown)
	{
		m_health--;
		m_playerDamageClock.restart();
		m_blinkTimer.restart();
		m_isVisible = false;
		m_takeDmgSound.setBuffer(*m_pGame->getPlayerTakeDamageBuff());
		m_takeDmgSound.play();
		if (m_health == 0)
			m_isDead = true;
		return true;
	}

	return false;
}
