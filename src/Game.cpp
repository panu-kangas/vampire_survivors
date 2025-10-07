#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "InputHandler.h"
#include "EndScreen.hpp"
#include "Weapon.h"
#include "Player.h"
#include "Rectangle.h"
#include "Vampire.h"
#include "VampireHandler.hpp"
#include "LevelHandler.hpp"
#include "StartScreen.hpp"
#include "utilities.hpp"


Game::Game() :
    m_state(State::START_SCREEN),
    m_pPlayer(std::make_unique<Player>(this))
{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
	m_pStartScreen = std::make_unique<StartScreen>(this);
	m_pEndScreen = std::make_unique<EndScreen>(this);
	m_levelHandler = std::make_unique<LevelHandler>(this);

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
	if (!m_backgroundMusic.openFromFile("assets/background_music.ogg")) {
		std::cerr << "Failed to load music!" << std::endl;
		return false;
	}
	if (!m_playerAttackMissBuff.loadFromFile("assets/player_attack_miss.ogg")) {
		std::cerr << "Failed to load SFX for player attack miss!" << std::endl;
		return false;
	}
	if (!m_playerAttackHitBuff.loadFromFile("assets/player_attack_hit.ogg")) {
		std::cerr << "Failed to load SFX for player attack hit!" << std::endl;
		return false;
	}

	m_backgroundMusic.setLoop(true);
	m_backgroundMusic.setVolume(50.f);
	m_backgroundMusic.play();

	m_floorSprite.setTexture(m_floorTexture);
    m_floorSprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
    m_floorSprite.setScale(2.0f, 2.0f);
	m_floorSprite.setColor(sf::Color(169, 169, 169));

	m_pPlayer->initialise();

    return true;
}

void Game::resetGame()
{
	m_levelHandler->initNewLevel(1);
	m_coinCount = 0;
    m_pPlayer->initialise();
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
			{
				m_pStartScreen->setIsReady(false);
				m_state = State::ACTIVE;
			}

			break ;
		}
            
        case State::ACTIVE:
        {
			m_pGameInput->update(deltaTime);
            m_levelHandler->update(deltaTime, m_pGameInput->getInputData());

            if (m_pPlayer->isDead())
            {
                m_state = State::GAME_OVER;
            }
			break ;
        }

		case State::GAME_OVER:
		{
			m_pEndScreen->handleInput(m_pGameInput->getInputData());
			if (m_pEndScreen->isReady())
			{
				resetGame();
				m_pEndScreen->setIsReady(false);
				m_state = State::START_SCREEN;
			}
		}

        break;
    }

}

void Game::drawFloor(sf::RenderTarget &target, bool isRed) const
{
	sf::Sprite tempSprite = m_floorSprite;
	if (isRed)
	{
		tempSprite.setColor(sf::Color::Red);
	}

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

    //  Draw texts.
	if (m_state == State::START_SCREEN)
	{
		m_pStartScreen->render(target, states);
	}
	else if (m_state == State::GAME_OVER)
	{
		m_pEndScreen->render(target, states);
	}
    else
    {
		m_levelHandler->render(target, states);
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

bool Game::isEnterPressed()
{
	return m_pGameInput->isEnterPressed();
}
