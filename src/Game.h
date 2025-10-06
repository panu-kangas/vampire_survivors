#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include "Constants.h"
#include "InfoBox.hpp"

class Player;
class Game;
class GameInput;
class Vampire;
class VampireHandler;
class StartScreen;
class EndScreen;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
		START_SCREEN,
        WAITING,
        ACTIVE,
		GAME_OVER
    };
    
    Game();
    ~Game();
    
    bool initialise();
    void update(float deltaTime);
	void updateScoreInfo();
    void resetLevel();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void drawFloor(sf::RenderTarget &target, bool isRed = false) const;

    State getState() const { return m_state; }
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

	int&	getScore() { return m_score; };
    Player* getPlayer() const;
	sf::Font* getFont() { return &m_font; }
    sf::Texture* getPlayerTexture() { return &m_playerTexture; }
	sf::Texture* getVampireTexture() { return &m_vampTexture; }

private:
    std::unique_ptr<Player> m_pPlayer;

    State m_state;
    std::unique_ptr<sf::Clock> m_pClock;
    std::unique_ptr<GameInput> m_pGameInput;
	std::unique_ptr<VampireHandler> m_vampireHandler;
	std::unique_ptr<StartScreen> m_pStartScreen;
	std::unique_ptr<EndScreen> m_pEndScreen;


	int m_score = 0;
	InfoBox m_scoreInfo;
    
    sf::Font m_font;
    sf::Texture m_playerTexture;
	sf::Texture m_vampTexture;
	sf::Texture m_floorTexture;
	sf::Sprite 	m_floorSprite;


};
