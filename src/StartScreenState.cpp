#include <iostream>
#include "Constants.h"
#include "StartScreenState.hpp"
#include "ResourceManager.h"

void drawText(sf::RenderTarget &target, sf::Font font, std::string text);


StartScreen::StartScreen(Game* gamePtr) : GameState(gamePtr)
{
	m_font = m_pGame->getFont();
}


void StartScreen::handleInput(sf::RenderTarget& target)
{
	

}

void StartScreen::update(float deltaTime)
{

}

void StartScreen::render(sf::RenderTarget& target)
{
	drawText(target, *m_font, "Welcome, Player!");
}