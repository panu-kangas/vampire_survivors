#include "LevelHandler.hpp"
#include "Player.h"
#include "Game.h"

LevelHandler::LevelHandler(Game* gamePtr) : m_pGame(gamePtr)
{
	initNewLevel(1);
}


void LevelHandler::initNewLevel(unsigned int levelId)
{
	LevelData& data = m_levelArr[levelId - 1];
	m_curLevelPtr = std::make_unique<Level>(m_pGame, data.levelId, data.vampireData);
	m_pUpgradeShop = std::make_unique<UpgradeShop>(m_pGame, data.vampireData);
	m_isShopActive = true;
}

void LevelHandler::update(float deltaTime, InputData& inputData)
{
	if (m_isShopActive)
	{
		m_pUpgradeShop->handleInput(inputData);
		m_pUpgradeShop->update(deltaTime);

		if (m_pUpgradeShop->isReady())
		{
			m_pUpgradeShop->initShop();
			m_isShopActive = false;
		}
		return ;
	}

	m_curLevelPtr->handleInput(inputData);
	m_curLevelPtr->update(deltaTime);

	if (m_curLevelPtr->isLevelPassed())
	{
		m_curLevelId++;
		initNewLevel(m_curLevelId);
	}
	else if (m_pGame->getPlayer()->isDead())
	{
		m_curLevelId = 1;
		m_pGame->setState(Game::State::GAME_OVER);
	}
}

void LevelHandler::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	if (m_isShopActive)
		m_pUpgradeShop->render(target, states);
	else
		m_curLevelPtr->render(target, states);
}