#pragma once

#include "Button.hpp"
#include "InfoBox.hpp"
#include "InputHandler.h"
#include "Weapon.h"

class UpgradeObject
{
	public:

	UpgradeObject() = delete;
	UpgradeObject(Game* gamePtr, Weapon* weapon);
	~UpgradeObject() = default;

	UpgradeObject(const UpgradeObject&) = delete;
	UpgradeObject& operator=(const UpgradeObject&) = delete;

	void handleInput(InputData& inputData);
	void update(float deltaTime);
    void render(sf::RenderTarget& target, sf::RenderStates& states);
	void handleUpgrade();

	void changeActiveButton();
	eButtonType getActiveButtonType() { return m_activeButtonPtr->getType(); };

	bool isActive() { return m_isActive; };
	void changeActiveStatus();

	private:

	void drawUpgradeLevelBoxes(sf::RenderTarget& target);

	InfoBox	m_backgroundBox;
	Button m_plusButton;
	Button m_minusButton;
	Button* m_activeButtonPtr; // IS THIS RISKY?
	Weapon* m_pWeapon;

	float m_upgradeValue;
	int m_upgradeLevelCount;

	bool m_isActive = false;


};