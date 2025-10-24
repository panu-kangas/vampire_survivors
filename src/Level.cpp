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
	m_vampireInfoBox(gamePtr, vampireData),
	m_scoreInfo(gamePtr),
	m_healthBox(gamePtr),
	m_weaponInfoBox(gamePtr, gamePtr->getPlayer()->getWeaponVec())
{
	m_vampireHandler = std::make_unique<VampireHandler>(gamePtr, *gamePtr->getVampireTexture(), vampireData.vampireSpawnRate);

	std::vector<std::string> infoText {
		"You will be facing",
		"",
		std::to_string(m_vampireData.whiteVampireCount) + "       " + std::to_string(m_vampireData.redVampireCount) \
		+ "       " +  std::to_string(m_vampireData.greenVampireCount),
		"",
	};

	m_healthBox.initInfoBox(infoText, 23.f, sf::Color(242, 134, 39, 200));
	m_healthBox.setPosition({0, 0});
	m_scoreInfo.initInfoBox({"Fight the vampires!"}, 23.f, sf::Color(242, 134, 39, 180));
}

void Level::handleInput(InputData& inputData)
{
	if (m_levelCanStart)
	{
		if (inputData.m_space && !inputData.m_spaceHold)
		{
			m_pGame->getPlayer()->attack(LANCE);
			inputData.m_spaceHold = true;
		}
		else if (inputData.m_vPressed && !inputData.m_vHold)
		{
			m_pGame->getPlayer()->attack(HOLY_PULSE);
			inputData.m_vHold = true;
		}
	}

	if (!m_levelCanStart && m_pGame->isEnterPressed())
	{
		m_levelCanStart = true;
	}

	if (m_isLevelPassed && m_pGame->isEnterPressed())
	{
		m_pGame->getPlayer()->initialise();
		m_isReady = true;
	}
}

void Level::handleProjectiles(Player* player, float deltaTime)
{
	for (auto& projectile : m_projectileVec)
	{
		projectile.update(deltaTime);
		if (projectile.collidesWith(player))
		{
			player->takeDamage();
			projectile.setAsDestroyed();
		}
	}

	int i = 0;
    while (i < m_projectileVec.size())
    {
        if (m_projectileVec[i].isDestroyed())
        {
            std::swap(m_projectileVec[i], m_projectileVec.back());
            m_projectileVec.pop_back();
            continue;
        }
        i++;
    }
}

void Level::update(float deltaTime)
{
	if (!m_levelCanStart)
		return ;

	updateInfoBoxes(deltaTime);

	if (m_isLevelPassed && !m_isReady)
		return ;

	Player* player = m_pGame->getPlayer();
    player->update(deltaTime);
	player->move(m_pGame->getInputData(), deltaTime);
	m_vampireHandler->vampireSpawner(deltaTime, m_vampireData);
    m_vampireHandler->update(deltaTime, m_pGame->getState());

	handleProjectiles(player, deltaTime);

	if (isVampireDataEmpty(m_vampireData) && m_vampireHandler->isVampireVecEmpty())
	{
		m_isLevelPassed = true;
	}

}

void Level::updateInfoBoxes(float deltaTime)
{
	if (m_isLevelPassed && !m_isReady)
	{
		m_scoreInfo.setText({"You cleared the level, wohoo! Press enter to continue"});
	}
	else
	{
		m_scoreInfo.setText({"Fight the vampires!"});
	}
	auto scoreInfoSize = m_scoreInfo.getSize();
	float infoX = ScreenWidth / 2 - scoreInfoSize.x / 2;
	float infoY = ScreenHeight - m_scoreInfo.getSize().y;
	m_scoreInfo.setPosition({infoX, infoY});

	std::vector<std::string> infoText = {
		"Health remaining",
		"",
		""
	};
	m_healthBox.setText(infoText);

	// Health icon logic (own function later) CHANGE LOCATION
	m_healthIcon.setOutlineColor(sf::Color::Black);
	m_healthIcon.setOutlineThickness(2.f);
	m_healthIcon.setSize({25.f, 25.f});

	m_vampireInfoBox.update(m_vampireData);
	m_weaponInfoBox.update(deltaTime);

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
		m_healthBox.render(target, states);
		m_vampireInfoBox.render(target, states);
		m_weaponInfoBox.render(target, states);

		for (auto& projectile : m_projectileVec)
		{
			projectile.draw(target, states);
		}

		// OWN SEPARATE FUNCTION
		float padding = 30.f;
		float gap = 15.f;
		float startX = m_healthBox.getPosition().x + padding;
		float posY = m_healthBox.getPosition().y + m_healthBox.getSize().y - padding - m_healthIcon.getSize().y;

		for (int i = 0; i < 3; ++i)
		{
			if (m_pGame->getPlayer()->getHealth() > i)
				m_healthIcon.setFillColor(sf::Color::Red);
			else
				m_healthIcon.setFillColor(sf::Color::Black);

			m_healthIcon.setPosition({startX, posY});
			target.draw(m_healthIcon);
			startX += gap + m_healthIcon.getSize().y;
		}
	}

}

void Level::renderIntroScreen(sf::RenderTarget& target, sf::RenderStates& states)
{
	sf::Font* font = m_pGame->getFont();
	drawHeaderText(target, *font, "Level " + std::to_string(m_levelId));
	drawCenteredText(target, *font, "Press Enter to start the level");
	m_vampireInfoBox.render(target, states);
}


