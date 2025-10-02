#pragma once

#include <SFML/Window/Keyboard.hpp>

class Player;
class Game;

struct InputData
{
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;
	bool m_enter = false;
    bool m_space = false;
    bool m_spaceHold = false;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight || m_space || m_enter;}
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer);
    ~GameInput();
    
    void update(float deltaTime);
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
	bool isEnterPressed() { return m_inputData.m_enter; };
    
    
private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
};
