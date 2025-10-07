#include "Level.hpp"
#include "LevelHandler.hpp"
#include "VampireHandler.hpp"
#include "Player.h"
#include "utilities.hpp"

#include <iostream>

Level::Level(Game* gamePtr, unsigned int levelId, VampireLevelData& vampireData) :
	GameState(gamePtr),
	m_levelId(levelId),
	m_vampireData(vampireData),
	m_levelInfoBox(gamePtr),
	m_scoreInfo(gamePtr)
{
	m_vampireHandler = std::make_unique<VampireHandler>(gamePtr, *gamePtr->getVampireTexture(), vampireData.vampireSpawnRate);

	std::vector<std::string> infoText {
		"You will be facing",
		"",
		std::to_string(m_vampireData.whiteVampireCount) + "  white vampires",
		std::to_string(m_vampireData.redVampireCount) + "  red vampires",
		std::to_string(m_vampireData.greenVampireCount) + "  green vampires",
		std::to_string(m_vampireData.bossVampireCount) + "  boss vampires",
	};
	m_levelInfoBox.setFontSize(23.f);
	m_levelInfoBox.setText(infoText);
	m_levelInfoBox.setColor(sf::Color(242, 134, 39, 200));
	auto instructionSize = m_levelInfoBox.getSize();
	float infoX = ScreenWidth / 2 - instructionSize.x / 2;
	float infoY = ScreenHeight * 0.6;
	m_levelInfoBox.setPosition({infoX, infoY});
}

void Level::handleInput(InputData& inputData)
{
	if (m_pGame->isEnterPressed())
	{
		m_levelCanStart = true;
	}
}

void Level::update(float deltaTime)
{
	if (!m_levelCanStart)
		return ;

	updateScoreInfo();
    m_pGame->getPlayer()->update(deltaTime);
	m_vampireHandler->vampireSpawner(deltaTime, m_vampireData);
    m_vampireHandler->update(deltaTime, m_pGame->getState());

	if (isVampireDataEmpty(m_vampireData) && m_vampireHandler->isVampireVecEmpty())
	{
		m_pGame->getPlayer()->initialise();
		m_isLevelPassed = true;
	}

}

void Level::updateScoreInfo()
{
	m_scoreInfo.setText(
		{"Your coins:  " + std::to_string(m_pGame->getCoins()),
		"Vampires left: " + std::to_string(m_vampireData.whiteVampireCount)}
	);
	m_scoreInfo.setColor(sf::Color(242, 134, 39, 180));
	auto scoreInfoSize = m_scoreInfo.getSize();
	float infoX = ScreenWidth / 2 - scoreInfoSize.x / 2;
	m_scoreInfo.setPosition({infoX, 0});
}

void Level::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	m_pGame->drawFloor(target);

	if (!m_levelCanStart)
	{
		renderIntroScreen(target, states);
	}
	else
	{
		m_scoreInfo.render(target, states);
		m_pGame->getPlayer()->draw(target, states);	
		m_vampireHandler->drawVampires(target, states);
	}
}

void Level::renderIntroScreen(sf::RenderTarget& target, sf::RenderStates& states)
{
	sf::Font* font = m_pGame->getFont();
	drawHeaderText(target, *font, "Level " + std::to_string(m_levelId));
	drawCenteredText(target, *font, "Press Enter to start the level");
	m_levelInfoBox.render(target, states);
}


