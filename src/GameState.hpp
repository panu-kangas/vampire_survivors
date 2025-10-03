#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

class GameState {
	public:

	GameState() = delete;
	GameState(Game* gamePtr) { m_pGame = gamePtr; };

    virtual ~GameState() = default;

    virtual void onEnter() {}
    virtual void handleInput(sf::RenderTarget& target) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
    virtual void onExit() {}

	protected:

	Game*   m_pGame;
};