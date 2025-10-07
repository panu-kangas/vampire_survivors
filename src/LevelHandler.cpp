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
}

void LevelHandler::update(float deltaTime, InputData& inputData)
{
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
	m_curLevelPtr->render(target, states);
}