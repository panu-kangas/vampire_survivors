#include <iostream>
#include "Constants.h"
#include "StartScreenState.hpp"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "VampireHandler.hpp"
#include "utilities.hpp"

StartScreen::StartScreen(Game* gamePtr) : GameState(gamePtr)
{
	m_font = m_pGame->getFont();
	m_pVampireHandler = std::make_unique<VampireHandler>(m_pGame, *m_pGame->getVampireTexture());
}

void StartScreen::handleInput(InputData inputData)
{
	if (inputData.m_enter)
	{
		m_isReady = true;
		m_pVampireHandler->initVampires();
	}

}

void StartScreen::update(float deltaTime)
{
	m_pVampireHandler->StartScreenVampireSpawner(deltaTime);
    m_pVampireHandler->update(deltaTime, Game::State::START_SCREEN);
}

void StartScreen::render(sf::RenderTarget& target, sf::RenderStates& states)
{
	m_pGame->drawFloor(target);
	m_pVampireHandler->drawVampires(target, states);
	drawHeaderText(target, *m_font, "Welcome, Player!");
	drawCenteredText(target, *m_font, "Press Enter to start the game.");
}
