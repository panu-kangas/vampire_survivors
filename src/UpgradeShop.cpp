#include "UpgradeShop.hpp"
#include "utilities.hpp"
#include "Constants.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

UpgradeShop::UpgradeShop(Game* gamePtr, VampireLevelData& vampireData) : 
	GameState(gamePtr),
	m_vampireInfoBox(gamePtr, vampireData),
	m_skillPointInfoBox(gamePtr),
	m_continueButton(gamePtr, CONTINUE)
{
	m_continueButton.initButton("Continue to next level", sf::Color(14, 158, 33), sf::Color(2, 107, 16));
	m_continueButton.setPosition({ScreenWidth / 2 - m_continueButton.getSize().x / 2, ScreenHeight * 0.85});

	Weapon* lance = m_pGame->getPlayer()->getWeaponVec()[0];
	Weapon* holyPulse = m_pGame->getPlayer()->getWeaponVec()[1];

	float boxY = ScreenHeight * 0.3;
	m_upgradeObjectVec.push_back(std::make_unique<UpgradeObject>(gamePtr, lance, boxY));
	m_upgradeObjectVec[0]->changeActiveStatus();

	float gap = 20.f;
	float box2Y = boxY + m_upgradeObjectVec[0]->getSize().y + gap;
	m_upgradeObjectVec.push_back(std::make_unique<UpgradeObject>(gamePtr, holyPulse, box2Y));

	float box3Y = box2Y + m_upgradeObjectVec[0]->getSize().y + gap;
	m_upgradeObjectVec.push_back(std::make_unique<UpgradeObject>(gamePtr, nullptr, box3Y));

	int& skillPoints = m_pGame->getPlayer()->getSkillPoints();
	m_skillPointInfoBox.initInfoBox({"Skill points left: ", "", std::to_string(skillPoints)}, 23.f, sf::Color(153, 108, 52));
	m_skillPointInfoBox.centerText();
	m_skillPointInfoBox.setPosition({ScreenWidth * 0.1, boxY});

}

void UpgradeShop::initShop()
{
	m_isReady = false;
}

void UpgradeShop::handleInput(InputData& inputData)
{
	// BREAK THIS LOGIC DOWN

	size_t maxIndex = m_upgradeObjectVec.size() - 1;
	if ((m_activeObjIndex == maxIndex && !m_continueButton.isActive() && m_pGame->isDownPressed())
			|| (m_continueButton.isActive() && m_pGame->isUpPressed())) 
	{
		m_upgradeObjectVec.back()->changeActiveStatus();
		m_continueButton.changeActiveStatus();
	}
	else if (m_activeObjIndex < maxIndex && m_pGame->isDownPressed())
	{
		eButtonType prevButtonType = m_upgradeObjectVec[m_activeObjIndex]->getActiveButtonType();
		m_upgradeObjectVec[m_activeObjIndex]->changeActiveStatus();
		m_activeObjIndex++;
		m_upgradeObjectVec[m_activeObjIndex]->changeActiveStatus();
		if (prevButtonType == eButtonType::PLUS)
			m_upgradeObjectVec[m_activeObjIndex]->changeActiveButton();
	}
	else if (m_activeObjIndex > 0 && m_pGame->isUpPressed())
	{
		eButtonType prevButtonType = m_upgradeObjectVec[m_activeObjIndex]->getActiveButtonType();
		m_upgradeObjectVec[m_activeObjIndex]->changeActiveStatus();
		m_activeObjIndex--;
		m_upgradeObjectVec[m_activeObjIndex]->changeActiveStatus();
		if (prevButtonType == eButtonType::PLUS)
			m_upgradeObjectVec[m_activeObjIndex]->changeActiveButton();
	}

	m_continueButton.handleInput(inputData);
	int& skillPoints = m_pGame->getPlayer()->getSkillPoints();
	if (m_continueButton.isPressed() && skillPoints == 0)
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
	int& skillPoints = m_pGame->getPlayer()->getSkillPoints();
	m_skillPointInfoBox.setText({"Skill points left: ", "", std::to_string(skillPoints)});
	
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
	m_skillPointInfoBox.render(target, states);
	drawHeaderText(target, *m_pGame->getFont(), "Welcome to Upgrade Shop!");

	for (auto& upgrade : m_upgradeObjectVec)
	{
		upgrade->render(target, states);
	}
}