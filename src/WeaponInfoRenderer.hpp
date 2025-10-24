#pragma once

#include "Weapon.h"
#include "Game.h"

class WeaponInfoRenderer
{
	public:

	WeaponInfoRenderer() = delete;
	WeaponInfoRenderer(Game* gamePtr, Weapon* weapon, sf::Vector2f position);

	void update(float deltaTime);
	void render(sf::RenderTarget& target);

	private:

	Game*	m_pGame;
	Weapon* m_weapon;

	sf::RectangleShape m_box;
	sf::Text m_text;
};