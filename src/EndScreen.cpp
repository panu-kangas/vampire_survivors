#include "Constants.h"
#include "EndScreen.hpp"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "VampireHandler.hpp"
#include "utilities.hpp"

EndScreen::EndScreen(Game* gamePtr) : GameState(gamePtr)
{
	m_font = m_pGame->getFont();
}

void EndScreen::handleInput(InputData& inputData)
{
	if (m_pGame->isEnterPressed())
	{
		m_isReady = true;
	}

}

void EndScreen::update(float deltaTime)
{

}

void EndScreen::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	m_pGame->drawFloor(target, true);
	drawHeaderText(target, *m_font, "You died!");
	std::string scoreString = std::to_string(m_pGame->getCoins());
	drawCenteredText(target, *m_font, "Your score was: " + scoreString);
	drawBottomText(target, *m_font, "Press Enter to play again!");
}
