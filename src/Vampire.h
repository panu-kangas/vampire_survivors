#pragma once

#include "Rectangle.h"

class Game;
class Player;

class Vampire : public Rectangle
{
public:
    Vampire(Game* game, sf::Vector2f position);
    virtual ~Vampire() {}
    
    virtual bool update(float deltaTime);
	virtual bool startScreenUpdate(float deltaTime);

	bool checkWeaponHits(Player* pPlayer);

    void setIsKilled(bool isKilled) { m_isKilled = isKilled; }
    bool isKilled() { return m_isKilled; }

protected:
    Game* m_pGame;
    bool m_isKilled = false;
	sf::Vector2f m_initPosition;
};
