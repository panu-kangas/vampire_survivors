#pragma once

#include "Button.hpp"
#include "InfoBox.hpp"
#include "InputHandler.h"
#include "Weapon.h"

class Game;

class UpgradeObject
{
	public:

	UpgradeObject() = delete;
	UpgradeObject(Game* gamePtr, Weapon* weapon, float posY);
	~UpgradeObject() = default;

	UpgradeObject(const UpgradeObject&) = delete;
	UpgradeObject& operator=(const UpgradeObject&) = delete;

	void handleInput(InputData& inputData);
	void update(float deltaTime);
    void render(sf::RenderTarget& target, sf::RenderStates& states);
	void handleUpgrade();

	void changeActiveButton();
	eButtonType getActiveButtonType() { return m_activeButtonPtr->getType(); };
	sf::Vector2f getSize() { return m_size; };

	bool isActive() { return m_isActive; };
	void changeActiveStatus();

	private:

	void drawUpgradeLevelBoxes(sf::RenderTarget& target);

	InfoBox	m_backgroundBox;
	Button m_plusButton;
	Button m_minusButton;
	Button* m_activeButtonPtr; // IS THIS RISKY?
	Weapon* m_pWeapon;
	Game* m_pGame;

	float m_upgradeValue;
	int m_upgradeLevelCount;
	sf::Vector2f m_size{400.f, 100.f};

	bool m_isActive = false;

};