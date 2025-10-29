#include <iostream>
#include "Constants.h"
#include "StartScreen.hpp"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "VampireHandler.hpp"
#include "utilities.hpp"

StartScreen::StartScreen(Game* gamePtr) : GameState(gamePtr), m_instructionBox(gamePtr)
{
	m_font = m_pGame->getFont();
	m_pVampireHandler = std::make_unique<VampireHandler>(m_pGame, *m_pGame->getVampireTexture(), 2.0f);

	std::vector<std::string> infoText {
		"",
		"You are being attacked by terrifying swarms of blood thirsty Vampires.",
		"Defeat them in order to survive!",
		"",
		"Luckily you have some skill points at your disposal.",
		"You can use these skill points before each level to boost your weapons and attributes.",
		"Good luck!",
		"",
		"Menu interaction:    Arrow keys + Enter",
		"Move Player:             Arrow Keys",
		"Use Lance:                 Space",
		"Use Holy Pulse:         V"
	};
	m_instructionBox.initInfoBox(infoText, 23.f, sf::Color(242, 134, 39, 200));
	auto instructionSize = m_instructionBox.getSize();
	float infoX = ScreenWidth / 2 - instructionSize.x / 2;
	float infoY = ScreenHeight * 0.4;
	m_instructionBox.setPosition({infoX, infoY});
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
	drawHeaderText(target, *m_font, "Vampires!");
	drawBottomText(target, *m_font, "Press Enter to start the game");
	m_instructionBox.render(target, states);
}
