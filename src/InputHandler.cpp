#include "Constants.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"

#include <iostream>

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{
}

GameInput::~GameInput()
{
    
}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
    }

    if (m_inputData.m_space && !m_inputData.m_spaceHold)
    {
        m_pPlayer->attack();
		m_inputData.m_spaceHold = true;
    }
}

void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = true;
    }
    else if (key == sf::Keyboard::Space)
    {
        m_inputData.m_space = true;
    }
	else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_enter = true;
    }
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = false;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = false;
    }
    else if (key == sf::Keyboard::Space)
    {
        m_inputData.m_space = false;
		m_inputData.m_spaceHold = false;
    }
	else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_enter = false;
    }
}

bool GameInput::isEnterPressed()
{
	if (m_enterClock.getElapsedTime().asSeconds() > EnterCooldown && m_inputData.m_enter)
	{
		m_enterClock.restart();
		return true;
	}
	return false;
}