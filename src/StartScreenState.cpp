#include <iostream>
#include "Constants.h"
#include "StartScreenState.hpp"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "utilities.hpp"

StartScreen::StartScreen(Game* gamePtr) : GameState(gamePtr)
{
	m_font = m_pGame->getFont();
}


void StartScreen::handleInput(InputData inputData)
{
	if (inputData.m_enter)
		m_isReady = true;

}

void StartScreen::update(float deltaTime)
{

}

void StartScreen::render(sf::RenderTarget& target)
{
	drawHeaderText(target, *m_font, "Welcome, Player!");
	drawCenteredText(target, *m_font, "Press Enter to start the game.");
}