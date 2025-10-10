#include "UpgradeObject.hpp"
#include "Constants.h"
#include "Game.h"
#include "Player.h"
#include "Weapon.h"
#include "utilities.hpp"


UpgradeObject::UpgradeObject(Game* gamePtr) : 
	m_backgroundBox(gamePtr),
	m_plusButton(gamePtr),
	m_minusButton(gamePtr)
{
	float lanceLength = gamePtr->getPlayer()->getWeapon()->getWeaponLength();
	m_backgroundBox.initInfoBox({"Update the Lance", "", floatToString(lanceLength)}, 23.f, sf::Color(242, 134, 39, 200));
	m_backgroundBox.setSize({400.f, 150.f});
	m_backgroundBox.centerText();
	float bgBoxX = ScreenWidth / 2 - m_backgroundBox.getSize().x / 2;
	float bgBoxY = ScreenHeight * 0.3;
	m_backgroundBox.setPosition({bgBoxX, bgBoxY});

	m_plusButton.initButton("+", sf::Color(14, 158, 33));
	m_plusButton.updateFontSize(30.f);
	float plusBtnX = m_backgroundBox.getPosition().x + m_backgroundBox.getSize().x * 0.2;
	float plusBtnY = m_backgroundBox.getPosition().y + m_backgroundBox.getSize().y / 2;
	m_plusButton.setPosition({plusBtnX, plusBtnY});
	m_plusButton.setToActive();

}

void UpgradeObject::handleInput(InputData& inputData)
{
	m_plusButton.handleInput(inputData);
}

void UpgradeObject::update(float deltaTime)
{
	m_plusButton.update(deltaTime);
}

void UpgradeObject::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	m_backgroundBox.render(target, states);
	m_plusButton.render(target, states);
}