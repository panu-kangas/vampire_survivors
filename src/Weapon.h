#pragma once

#include "Rectangle.h"
#include "Constants.h"

class Weapon : public Rectangle
{
public:

    Weapon();
    virtual ~Weapon() {}

    void setActive(bool isActive);
    void update(float deltaTime);
    bool isActive() { return m_isActive; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	float getWeaponLength() { return m_weaponLength; };
	void setWeaponLength(float newLength) { m_weaponLength = newLength; };

private:

    bool m_isActive = false;
    float m_timer = 0.0f;
	float m_weaponLength = WeaponWidth;

};