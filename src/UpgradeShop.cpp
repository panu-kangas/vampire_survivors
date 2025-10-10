#include "UpgradeShop.hpp"
#include "utilities.hpp"
#include "Constants.h"


UpgradeShop::UpgradeShop(Game* gamePtr, VampireLevelData& vampireData) : 
	GameState(gamePtr),
	m_vampireInfoBox(gamePtr, vampireData),
	m_lanceUpgrade(gamePtr),
	m_continueButton(gamePtr)
{
	m_continueButton.initButton("Continue to next level", sf::Color(14, 158, 33));
	m_continueButton.setPosition({ScreenWidth / 2 - m_continueButton.getSize().x / 2, ScreenHeight * 0.85});

}

void UpgradeShop::initShop()
{
	m_isReady = false;
}

void UpgradeShop::handleInput(InputData& inputData)
{
	m_continueButton.handleInput(inputData);
	if (m_continueButton.isPressed())
	{
		m_isReady = true;
	}
}

void UpgradeShop::update(float deltaTime)
{
}

void UpgradeShop::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	m_pGame->drawFloor(target);
	m_vampireInfoBox.render(target, states);
	m_lanceUpgrade.render(target, states);
	m_continueButton.render(target, states);
	drawHeaderText(target, *m_pGame->getFont(), "Welcome to Upgrade Shop!");
}