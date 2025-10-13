#include "VampireInfoBox.hpp"
#include "Game.h"
#include "Constants.h"

VampireInfoBox::VampireInfoBox(Game* gamePtr, VampireLevelData& vampireData)
{
	m_pGame = gamePtr;
	m_font = gamePtr->getFont();

	m_vampireCountVec.push_back(vampireData.whiteVampireCount);
	m_vampireCountVec.push_back(vampireData.redVampireCount);
	m_vampireCountVec.push_back(vampireData.greenVampireCount);

	// Set up icon vector
	sf::Sprite tempSprite;
	tempSprite.setTexture(*gamePtr->getVampireTexture());
    tempSprite.setScale(1.6f, 1.6f);
	tempSprite.setOrigin(tempSprite.getLocalBounds().width / 2, tempSprite.getLocalBounds().height / 2);
	m_iconVec.push_back(tempSprite);
	tempSprite.setColor(sf::Color::Red);
	m_iconVec.push_back(tempSprite);
	tempSprite.setColor(sf::Color::Green);
	m_iconVec.push_back(tempSprite);

	// Set up header text
	m_headerText.setFont(*m_font);
    m_headerText.setCharacterSize(m_fontSize);
	m_headerText.setString("You will be facing next:");

	m_size.x = 40.f + m_headerText.getLocalBounds().width;
	m_size.y = 40.f + tempSprite.getLocalBounds().height + m_headerText.getLocalBounds().height + 40.f;
	m_position = {0.f, ScreenHeight - m_size.y};

	m_headerText.setPosition(m_position.x + (m_size.x / 2 - m_headerText.getLocalBounds().width / 2), m_position.y + 10.f);

	float startX = m_size.x / 6 - 10.f; // in the middle of first third of the box
	float posY = m_position.y + m_size.y - 5.f - tempSprite.getLocalBounds().height;
	float gap = m_size.x / 3;

	for (auto& icon : m_iconVec)
	{
		icon.setPosition(startX, posY);
		startX += gap;
	}

	sf::Text tempText;
	tempText.setFont(*m_font);
	tempText.setCharacterSize(m_fontSize - 5);

	for (int i = 0; i < 3; ++i)
	{
		tempText.setString(std::to_string(m_vampireCountVec[i]));
		tempText.setOrigin(tempText.getLocalBounds().width / 2, tempText.getLocalBounds().height / 2);
		tempText.setPosition(m_iconVec[i].getPosition().x + m_iconVec[i].getLocalBounds().width + 15.f,  m_iconVec[i].getPosition().y - 5.f);
		m_vampireCountTextVec.push_back(tempText);
	}
	
}

void VampireInfoBox::update(VampireLevelData& vampireData)
{
	m_vampireCountTextVec[0].setString(std::to_string(vampireData.whiteVampireCount));
	m_vampireCountTextVec[1].setString(std::to_string(vampireData.redVampireCount));	
	m_vampireCountTextVec[2].setString(std::to_string(vampireData.greenVampireCount));

	if (m_pGame->hasLevelStarted() && m_firstHeader)
	{
		m_firstHeader = false;
		m_headerText.setString("Vampires left:");
		m_headerText.setPosition(m_position.x + (m_size.x / 2 - m_headerText.getLocalBounds().width / 2), m_position.y + 10.f);
	}

}

void VampireInfoBox::render(sf::RenderTarget& target, sf::RenderStates& states) const
{
 	sf::RectangleShape background(m_size);
    background.setPosition(m_position);
    background.setFillColor(m_bgColor);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2.f);
    target.draw(background);

	target.draw(m_headerText);
	
	for (auto& icon : m_iconVec)
	{
		target.draw(icon);
	}

	for (auto& text : m_vampireCountTextVec)
	{
		target.draw(text);
	}
}
