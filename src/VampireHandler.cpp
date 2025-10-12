#include "Constants.h"
#include "Game.h"
#include "VampireHandler.hpp"
#include "ResourceManager.h"
#include "Vampire.h"
#include "RedVampire.hpp"
#include "utilities.hpp"

#include <iostream>

VampireHandler::VampireHandler(Game* pGame, sf::Texture& vampTexture, float vampireSpawnRate) : 
	m_pGame(pGame),
	m_vampTexture(vampTexture)
{
	m_vampireCooldown = vampireSpawnRate;
	m_nextVampireCooldown = m_vampireCooldown;
}

VampireTypes VampireHandler::getVampireType(VampireLevelData& vampireData)
{
	std::vector<std::pair<VampireTypes, unsigned>> vampireCounts {
		{WHITE_VAMPIRE, vampireData.whiteVampireCount},
		{RED_VAMPIRE, vampireData.redVampireCount},
		{GREEN_VAMPIRE, vampireData.greenVampireCount},
		{BOSS_VAMPIRE, vampireData.bossVampireCount}
	};
	
	unsigned totalVampires = 0;
	for (auto& pair : vampireCounts)
	{
		totalVampires += pair.second;
	}

	int roll = rand() % totalVampires;

	int idx = 0;
	for (int i = 0; i < vampireCounts.size(); ++i)
	{
		roll -= vampireCounts[i].second;
		if (roll <= 0)
		{
			idx = i;
			break ;
		}
	}

	return vampireCounts[idx].first;
}

void VampireHandler::addVampireToVec(sf::Vector2f& position, VampireTypes& type, VampireLevelData& vampireData)
{
	switch (type)
	{
		case WHITE_VAMPIRE:
		{
			if (vampireData.whiteVampireCount > 0)
			{
				m_pVampires.push_back(std::make_unique<Vampire>(m_pGame, position));
				vampireData.whiteVampireCount--;
				break ;
			}
		}

		case RED_VAMPIRE:
		{
			if (vampireData.redVampireCount > 0)
			{
				m_pVampires.push_back(std::make_unique<RedVampire>(m_pGame, position));
				vampireData.redVampireCount--;
				break ;
			}
		}

		case GREEN_VAMPIRE:
		{
			break ;
		}

		case BOSS_VAMPIRE:
		{
			break ;
		}

		default:
		{
			break ;
		}
	}
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

	VampireTypes type = getVampireType(vampireData);

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
	addVampireToVec(spawnPosition, type, vampireData);

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