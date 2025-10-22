#pragma once

#include "Weapon.h"


class HolyPulse : public Weapon
{
	public:

	HolyPulse() = delete;
	HolyPulse(std::string name);
	~HolyPulse() = default;

	void update(float deltaTime, Player* playerPtr) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setActive(bool isActive) override;
	float getRadius() { return m_radius; };


	private:

	float m_radius = HolyPulseRadius;
	bool m_isPulseStarted = false;
	sf::CircleShape m_circle;


};