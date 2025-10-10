#include "UpgradeObject.hpp"
#include "Constants.h"


UpgradeObject::UpgradeObject(Game* gamePtr) : 
	m_backgroundBox(gamePtr)
{
	m_backgroundBox.initInfoBox({"Update the Lance"}, 23.f, sf::Color(242, 134, 39, 200));
	m_backgroundBox.setSize({400.f, 150.f});
	m_backgroundBox.centerText();
	float bgBoxX = ScreenWidth / 2 - m_backgroundBox.getSize().x / 2;
	float bgBoxY = ScreenHeight * 0.3;
	m_backgroundBox.setPosition({bgBoxX, bgBoxY});
}

void UpgradeObject::handleInput(InputData& inputData)
{

}

void UpgradeObject::update(float deltaTime)
{

}

void UpgradeObject::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	m_backgroundBox.render(target, states);
}