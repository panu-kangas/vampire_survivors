#pragma once

#include "Weapon.h"


class HolyPulse : public Weapon
{
	public:

	HolyPulse() = delete;
	HolyPulse(std::string name);
	~HolyPulse() = default;

	void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:

	float m_radius = 40.f;

};