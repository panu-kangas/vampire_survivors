#include <iostream>
#include "Constants.h"
#include "StartScreen.hpp"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "VampireHandler.hpp"
#include "utilities.hpp"

StartScreen::StartScreen(Game* gamePtr) : GameState(gamePtr), instructionBox(gamePtr)
{
	m_font = m_pGame->getFont();
	m_pVampireHandler = std::make_unique<VampireHandler>(m_pGame, *m_pGame->getVampireTexture(), 2.0f);

	std::vector<std::string> infoText {
		"INSTRUCTIONS",
		"",
		"Try to survive as long as you can against an endless swarm of blood thirsty Vampires!",
		"",
		"You get coins for slaying vampires.",
		"After each level, you can use your coins to buy new weapons.",
		"",
		"Move: Arrow keys",
		"Hit enemies: Space"
	};
	instructionBox.setFontSize(23.f);
	instructionBox.setText(infoText);
	instructionBox.setColor(sf::Color(242, 134, 39, 200));
	auto instructionSize = instructionBox.getSize();
	float infoX = ScreenWidth / 2 - instructionSize.x / 2;
	float infoY = ScreenHeight * 0.6;
	instructionBox.setPosition({infoX, infoY});
}

void StartScreen::handleInput(InputData& inputData)
{
	if (m_pGame->isEnterPressed())
	{
		m_isReady = true;
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
	drawCenteredText(target, *m_font, "Press Enter to start the game");
	instructionBox.render(target, states);
}
