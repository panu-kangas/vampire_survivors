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
	if (m_isWin)
	{
		m_pGame->drawFloor(target, GREEN);
		drawHeaderText(target, *m_font, "You win!");
		drawCenteredText(target, *m_font, "You are an amazing vampire slayer, congrats!", -30.f);
	}
	else
	{
		m_pGame->drawFloor(target, RED);
		drawHeaderText(target, *m_font, "You died!");
	}
	std::string scoreString = std::to_string(m_pGame->getCoins());
	drawCenteredText(target, *m_font, "Your score was:", 40.f);
	drawCenteredText(target, *m_font, scoreString, 96.f);
	drawBottomText(target, *m_font, "Press Enter to play again!");
}
