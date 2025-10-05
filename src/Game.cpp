#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Rectangle.h"
#include "Vampire.h"
#include "VampireHandler.hpp"
#include "StartScreenState.hpp"
#include "utilities.hpp"


Game::Game() :
    m_state(State::START_SCREEN),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>(this))
{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
	m_pStartScreen = std::make_unique<StartScreen>(this);
}

Game::~Game()
{
}

bool Game::initialise()
{
    /*
        PAY ATTENTION HIVER!
            If you want to load any assets (fonts, textures) please use the pattern shown below
    */

    if (!m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf")))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    if (!m_vampTexture.loadFromFile(ResourceManager::getFilePath("vampire.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }
    if (!m_playerTexture.loadFromFile(ResourceManager::getFilePath("player.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }
	if (!m_floorTexture.loadFromFile(ResourceManager::getFilePath("floor.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }

	m_floorSprite.setTexture(m_floorTexture);
    m_floorSprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
    m_floorSprite.setScale(2.0f, 2.0f);

	m_vampireHandler = std::make_unique<VampireHandler>(this, m_vampTexture);

    resetLevel();
    return true;
}

void Game::resetLevel()
{
    m_vampireHandler->initVampires();

	m_score = 0;
    m_pPlayer->initialise();
    m_pClock->restart();
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
		case State::START_SCREEN:
		{
			m_pStartScreen->handleInput(m_pGameInput->getInputData());
			m_pStartScreen->update(deltaTime);
			if (m_pStartScreen->isReady())
				m_state = State::WAITING;

			break ;
		}
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
            {
                m_state = State::ACTIVE;
                m_pClock->restart();
            }
        }
        break;
            
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->update(deltaTime);

            m_vampireHandler->vampireSpawner(deltaTime);
            m_vampireHandler->update(deltaTime, m_state);

            if (m_pPlayer->isDead())
            {
                m_state = State::GAME_OVER;
                resetLevel();
            }
        }

		case State::GAME_OVER:
		{
			if (m_pGameInput->isEnterPressed())
			{
				m_state = State::WAITING;
			}
		}

        break;
    }

}

void Game::drawFloor(sf::RenderTarget &target) const
{
	sf::Sprite tempSprite = m_floorSprite;

	// -10 because the sprite had rounded corners --> empty spot in top left corner
	for (int x = -10; x < ScreenWidth; x += tempSprite.getLocalBounds().width)
	{
		for (int y = 0; y < ScreenHeight; y += tempSprite.getLocalBounds().height)
		{
			tempSprite.setPosition(x, y);
			target.draw(tempSprite);
		}
	}
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_state != State::START_SCREEN)
		drawFloor(target);

    //  Draw texts.
	if (m_state == State::START_SCREEN)
	{
		m_pStartScreen->render(target, states);
	}
    else if (m_state == State::WAITING)
    {
        drawText(target, m_font, "Game Start!!");
    }
	else if (m_state == State::GAME_OVER)
	{
        drawText(target, m_font, "You Died!! Press enter to restart");
	}
    else
    {
        sf::Text timerText;
        timerText.setFont(m_font);
        timerText.setFillColor(sf::Color::White);
        timerText.setStyle(sf::Text::Bold);
        timerText.setString(std::to_string((int)m_pClock->getElapsedTime().asSeconds()));
        timerText.setPosition(sf::Vector2f((ScreenWidth - timerText.getLocalBounds().getSize().x) * 0.5, 20));
        target.draw(timerText);

		sf::Text scoreText;
        scoreText.setFont(m_font);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setString("Your score: " + std::to_string(m_score));
        scoreText.setPosition(sf::Vector2f((ScreenWidth - scoreText.getLocalBounds().width) - 30, 20));
        target.draw(scoreText);
    }

	
	if (m_state != State::START_SCREEN)
	{
		// Draw player.
		m_pPlayer->draw(target, states);
		
		m_vampireHandler->drawVampires(target, states);
	}
   
}


void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}

Player* Game::getPlayer() const 
{
    return m_pPlayer.get();
}
