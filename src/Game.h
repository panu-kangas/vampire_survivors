#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Constants.h"
#include "InfoBox.hpp"

class Player;
class Game;
class GameInput;
class Vampire;
class VampireHandler;
class LevelHandler;
class StartScreen;
class EndScreen;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
		START_SCREEN,
        ACTIVE,
		GAME_OVER
    };
    
    Game();
    ~Game();
    
    bool initialise();
    void update(float deltaTime);
	void updateScoreInfo();
    void resetGame();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    State getState() const { return m_state; }
	void drawFloor(sf::RenderTarget &target, bool isRed = false) const;
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
	bool isEnterPressed();

	int&	getCoins() { return m_coinCount; };
    Player* getPlayer() const;
	sf::Font* getFont() { return &m_font; }
    sf::Texture* getPlayerTexture() { return &m_playerTexture; }
	sf::Texture* getVampireTexture() { return &m_vampTexture; }
	sf::Sprite*   getFloorSprite() { return &m_floorSprite; };
	sf::SoundBuffer* getPlayerAttackHitBuff() { return &m_playerAttackHitBuff; };
	sf::SoundBuffer* getPlayerAttackMissBuff() { return &m_playerAttackMissBuff; };

private:
    std::unique_ptr<Player> m_pPlayer;

    State m_state;
    std::unique_ptr<GameInput> m_pGameInput;
	std::unique_ptr<LevelHandler> m_levelHandler;
	std::unique_ptr<StartScreen> m_pStartScreen;
	std::unique_ptr<EndScreen> m_pEndScreen;

	int m_coinCount = 0;
    
    sf::Font m_font;
    sf::Texture m_playerTexture;
	sf::Texture m_vampTexture;
	sf::Texture m_floorTexture;
	sf::Sprite 	m_floorSprite;

	sf::Music m_backgroundMusic;
	sf::SoundBuffer m_playerAttackMissBuff;
	sf::SoundBuffer m_playerAttackHitBuff;

};
