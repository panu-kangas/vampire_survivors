#pragma once

#include "Rectangle.h"

class Game;

class Vampire : public Rectangle
{
public:
    Vampire(Game* game, sf::Vector2f position);
    virtual ~Vampire() {}
    
    bool update(float deltaTime);
	bool startScreenUpdate(float deltaTime);

    void setIsKilled(bool isKilled) { m_isKilled = isKilled; }
    bool isKilled() { return m_isKilled; }

private:
    Game* m_pGame;
    bool m_isKilled = false;
	sf::Vector2f m_initPosition;
};
