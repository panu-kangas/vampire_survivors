#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Constants.h"
#include "InputHandler.h"
#include "Enums.hpp"

class Player;
class Projectile;
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
    void resetGame();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    State getState() const { return m_state; }
	void setState(State newState) { m_state = newState; };
	void drawFloor(sf::RenderTarget &target, eFloorColor color = NORMAL) const;

	void addNewProjectile(Projectile& newProjectile);
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
	bool isEnterPressed();
	bool isDownPressed();
	bool isUpPressed();
	bool hasLevelStarted();

	int&	getCoins() { return m_coinCount; };
    Player* getPlayer() const;
	sf::Font* getFont() { return &m_font; }
    sf::Texture* getPlayerTexture() { return &m_playerTexture; }
	sf::Texture* getVampireTexture() { return &m_vampTexture; }
	sf::Sprite*   getFloorSprite() { return &m_floorSprite; };
	sf::Texture* getGreenVampireBulletTexture() { return &m_greenVampireBulletTexture; };
	sf::SoundBuffer* getPlayerAttackBuff() { return &m_playerAttackBuff; };
	sf::SoundBuffer* getPlayerTakeDamageBuff() { return &m_playerTakeDamageBuff; };
	InputData& getInputData() { return m_pGameInput->getInputData(); };
	void setEndStatus(bool status);

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
	sf::Texture m_greenVampireBulletTexture;

	sf::Music m_backgroundMusic;
	sf::SoundBuffer m_playerAttackBuff;
	sf::SoundBuffer m_playerTakeDamageBuff;

};
