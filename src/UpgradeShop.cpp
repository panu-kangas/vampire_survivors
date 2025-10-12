#include "UpgradeShop.hpp"
#include "utilities.hpp"
#include "Constants.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

UpgradeShop::UpgradeShop(Game* gamePtr, VampireLevelData& vampireData) : 
	GameState(gamePtr),
	m_vampireInfoBox(gamePtr, vampireData),
	m_continueButton(gamePtr, CONTINUE)
{
	m_continueButton.initButton("Continue to next level", sf::Color(14, 158, 33), sf::Color(2, 107, 16));
	m_continueButton.setPosition({ScreenWidth / 2 - m_continueButton.getSize().x / 2, ScreenHeight * 0.85});

	m_upgradeObjectVec.push_back(std::make_unique<UpgradeObject>(gamePtr, m_pGame->getPlayer()->getWeapon()));
	m_upgradeObjectVec[0]->changeActiveStatus();

}

void UpgradeShop::initShop()
{
	m_isReady = false;
}

void UpgradeShop::handleInput(InputData& inputData)
{

	if (m_upgradeObjectVec[0]->isActive() && inputData.m_movingDown)
	{
		m_upgradeObjectVec[0]->changeActiveStatus();
		m_continueButton.changeActiveStatus();
	}
	else if (m_continueButton.isActive() && inputData.m_movingUp)
	{
		m_continueButton.changeActiveStatus();
		m_upgradeObjectVec[0]->changeActiveStatus();
	}

	m_continueButton.handleInput(inputData);
	if (m_continueButton.isPressed())
	{
		m_isReady = true;
		for (auto& upgrade : m_upgradeObjectVec)
		{
			upgrade->handleUpgrade();
		}
	}

	for (auto& upgrade : m_upgradeObjectVec)
	{
		upgrade->handleInput(inputData);
	}
}

void UpgradeShop::update(float deltaTime)
{
	for (auto& upgrade : m_upgradeObjectVec)
	{
		upgrade->update(deltaTime);
	}
}

void UpgradeShop::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	m_pGame->drawFloor(target);
	m_vampireInfoBox.render(target, states);
	m_continueButton.render(target, states);
	drawHeaderText(target, *m_pGame->getFont(), "Welcome to Upgrade Shop!");

	for (auto& upgrade : m_upgradeObjectVec)
	{
		upgrade->render(target, states);
	}
}