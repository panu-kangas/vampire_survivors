#include "Constants.h"
#include "Game.h"
#include "VampireHandler.hpp"
#include "ResourceManager.h"
#include "Vampire.h"
#include "utilities.hpp"

#include <iostream>

VampireHandler::VampireHandler(Game* pGame, sf::Texture& vampTexture, float vampireSpawnRate) : 
	m_pGame(pGame),
	m_vampTexture(vampTexture)
{
	m_vampireCooldown = vampireSpawnRate;
	m_nextVampireCooldown = m_vampireCooldown;
}

void VampireHandler::vampireSpawner(float deltaTime, VampireLevelData& vampireData)
{
	if (isVampireDataEmpty(vampireData))
		return ;
	
    if (m_nextVampireCooldown > 0.0f)
    {
        m_nextVampireCooldown -= deltaTime;
        return;
    }

    float randomXPos = rand() % ScreenWidth;
    float randomYPos = rand() % ScreenHeight;

    float distToRight = (float) ScreenWidth - randomXPos;
    float distToBottom = (float) ScreenHeight - randomYPos;

    float xMinDist = randomXPos < distToRight ? -randomXPos : distToRight;
    float yMinDist = randomYPos < distToBottom ? -randomYPos : distToBottom;

    if (std::abs(xMinDist) < std::abs(yMinDist))
        randomXPos += xMinDist;
    else
        randomYPos += yMinDist;

    sf::Vector2f spawnPosition = sf::Vector2f(randomXPos, randomYPos);
    m_pVampires.push_back(std::make_unique<Vampire>(m_pGame, spawnPosition));

	if (vampireData.whiteVampireCount > 0)
		vampireData.whiteVampireCount--;

	m_nextVampireCooldown = m_vampireCooldown;

	
}

void VampireHandler::StartScreenVampireSpawner(float deltaTime)
{
    if (m_nextVampireCooldown > 0.0f)
    {
        m_nextVampireCooldown -= deltaTime;
        return;
    }

    float randomXPos = rand() % ScreenWidth;
    float randomYPos = rand() % ScreenHeight;

	if (randomXPos > ScreenWidth / 2)
		randomXPos = ScreenWidth;
	else
		randomXPos = 0 - VampireWidth;
	
    sf::Vector2f spawnPosition = sf::Vector2f(randomXPos, randomYPos);
    m_pVampires.push_back(std::make_unique<Vampire>(m_pGame, spawnPosition));

	m_nextVampireCooldown = m_vampireCooldown;

}

void 	VampireHandler::update(float deltaTime, Game::State gameState)
{
	for (auto& temp : m_pVampires)
	{
		if (gameState == Game::State::START_SCREEN)
		{
			temp->startScreenUpdate(deltaTime);
		}
		else
		{
			bool vampireDied = temp->update(deltaTime);
			if (vampireDied)
				m_pGame->getCoins()++;
		}
	}

	int i = 0;
    while (i < m_pVampires.size())
    {
        if (m_pVampires[i]->isKilled())
        {
            std::swap(m_pVampires[i], m_pVampires.back());
            m_pVampires.pop_back();
            continue;
        }
        i++;
    }
}

void VampireHandler::drawVampires(sf::RenderTarget &target, sf::RenderStates states)
{
	for (auto& temp : m_pVampires)
	{
		temp->draw(target, states);
	}
}