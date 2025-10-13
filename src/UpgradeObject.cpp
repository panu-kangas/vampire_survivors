#include "UpgradeObject.hpp"
#include "Constants.h"
#include "Game.h"
#include "Player.h"
#include "Weapon.h"
#include "utilities.hpp"

#include <iostream>


UpgradeObject::UpgradeObject(Game* gamePtr, Weapon* weapon, float posY) : 
	m_pGame(gamePtr),
	m_backgroundBox(gamePtr),
	m_plusButton(gamePtr, PLUS),
	m_minusButton(gamePtr, MINUS),
	m_pWeapon(weapon)
{

	if (!weapon)
	{
		m_upgradeValue = gamePtr->getPlayer()->getSpeed();
		m_upgradeLevelCount = gamePtr->getPlayer()->getUpgradeLevel();
	}
	else
	{
		m_upgradeValue = *m_pWeapon->getUpgradeValue();
		m_upgradeLevelCount = m_pWeapon->getUpgradeLevel();
	}

	m_backgroundBox.initInfoBox({}, 23.f, sf::Color(242, 134, 39, 200)); // Update handels text insertion
	this->update(0.f); // No need for deltaTime in initial update call
	float bgBoxX = ScreenWidth / 2 - m_backgroundBox.getSize().x / 2;
	m_backgroundBox.setPosition({bgBoxX, posY});

	m_plusButton.initButton("+", sf::Color(14, 158, 33), sf::Color(2, 107, 16));
	m_plusButton.updateFontSize(30.f);
	float plusBtnX = m_backgroundBox.getPosition().x + m_backgroundBox.getSize().x * 0.8 - m_plusButton.getSize().x;
	float plusBtnY = m_backgroundBox.getPosition().y + m_backgroundBox.getSize().y * 0.5 + 10.f;
	m_plusButton.setPosition({plusBtnX, plusBtnY});

	m_minusButton.initButton("-", sf::Color(199, 39, 28), sf::Color(128, 12, 4));
	m_minusButton.updateFontSize(30.f);
	m_minusButton.setSize(m_plusButton.getSize());
	float minusBtnX = m_backgroundBox.getPosition().x + m_backgroundBox.getSize().x * 0.2;
	float minusBtnY = m_backgroundBox.getPosition().y + m_backgroundBox.getSize().y * 0.5 + 10.f;
	m_minusButton.setPosition({minusBtnX, minusBtnY});

	m_activeButtonPtr = &m_minusButton; // IS THIS RISKY?

}

void UpgradeObject::handleUpgrade()
{
	if (!m_pWeapon)
	{
		m_pGame->getPlayer()->upgradeSpeed(m_upgradeValue, m_upgradeLevelCount);
	}
	else
	{
		m_pWeapon->handleUpgrade(m_upgradeValue, m_upgradeLevelCount);
	}
}

void UpgradeObject::changeActiveStatus()
{
	if (m_isActive)
	{
		if (m_minusButton.isActive())
			m_minusButton.changeActiveStatus();
		else if (m_plusButton.isActive())
			m_plusButton.changeActiveStatus();
	}
	else
	{
		if (!m_minusButton.isActive())
		{
			m_minusButton.changeActiveStatus();
			m_activeButtonPtr = &m_minusButton;
		}
	}

	m_isActive = !m_isActive;
	m_backgroundBox.changeActiveStatus();
}


void UpgradeObject::changeActiveButton()
{
	m_activeButtonPtr->changeActiveStatus();

	if (m_activeButtonPtr == &m_minusButton)
		m_activeButtonPtr = &m_plusButton;
	else
		m_activeButtonPtr = &m_minusButton;

	m_activeButtonPtr->changeActiveStatus();
}


void UpgradeObject::handleInput(InputData& inputData)
{
	if (!m_isActive)
		return ;

	if ((this->getActiveButtonType() == PLUS && inputData.m_movingLeft)
		|| (this->getActiveButtonType() == MINUS && inputData.m_movingRight))
	{
		this->changeActiveButton();
	}

	m_plusButton.handleInput(inputData);
	m_minusButton.handleInput(inputData);

	float upgradeScale = 0;
	if (!m_pWeapon)
	{
		upgradeScale = m_pGame->getPlayer()->getUpgradeScale();
	}
	else
	{
		upgradeScale = m_pWeapon->getUpgradeScale();
	}
	
	int& skillPoints = m_pGame->getPlayer()->getSkillPoints();
	if (m_upgradeLevelCount < maxUpgradeLevel && skillPoints > 0 && m_plusButton.isPressed())
	{
		m_upgradeValue += upgradeScale;
		m_upgradeLevelCount++;
		skillPoints--;
	}
	else if (m_upgradeLevelCount > 1 && m_minusButton.isPressed())
	{
		m_upgradeValue -= upgradeScale;
		m_upgradeLevelCount--;
		skillPoints++;
	}
}

void UpgradeObject::update(float deltaTime)
{

	std::string upgradeName = !m_pWeapon ? "Upgrade Speed" : "Upgrade " + m_pWeapon->getName();

	std::vector<std::string> infoText {
		upgradeName,
		"",
		floatToString(m_upgradeValue, 2)
	};
	m_backgroundBox.setText(infoText);
	m_backgroundBox.setSize(m_size);
	m_backgroundBox.centerText();

	m_plusButton.update(deltaTime);
	m_minusButton.update(deltaTime);
}

void UpgradeObject::drawUpgradeLevelBoxes(sf::RenderTarget& target)
{
	sf::RectangleShape tempRect;
	float boxGap = 5.0f;
	tempRect.setSize({10.f, 10.f});

	float startX = m_backgroundBox.getPosition().x + 10.f;
	float posY = m_backgroundBox.getPosition().y + 10.f;

	for (int i = 0; i < maxUpgradeLevel; ++i)
	{
		if (i < m_upgradeLevelCount)
			tempRect.setFillColor(sf::Color::Green);
		else
			tempRect.setFillColor(sf::Color::Black);

		tempRect.setPosition(startX, posY);
		startX += tempRect.getSize().x + boxGap;
		target.draw(tempRect);
	}
}


void UpgradeObject::render(sf::RenderTarget& target, sf::RenderStates& states)
{

	m_backgroundBox.render(target, states);
	this->drawUpgradeLevelBoxes(target);
	m_plusButton.render(target, states);
	m_minusButton.render(target, states);
}