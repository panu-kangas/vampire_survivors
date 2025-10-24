#pragma once

#include <vector>

#include "Weapon.h"
#include "WeaponInfoRenderer.hpp"
#include "InfoBox.hpp"

class Game;
class Weapon;


class WeaponInfoBox
{
	public:

	WeaponInfoBox() = delete;
	WeaponInfoBox(Game* gamePtr, std::vector<Weapon*> weaponVec);
	~WeaponInfoBox() = default;

	void update(float deltaTime);
	void render(sf::RenderTarget& target, sf::RenderStates states);

	private:

	std::vector<Weapon*> m_weaponVec;
	std::vector<WeaponInfoRenderer> m_renderVec;
	InfoBox m_bgBox;

};