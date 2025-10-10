#pragma once

#include "Button.hpp"
#include "InfoBox.hpp"
#include "InputHandler.h"

class UpgradeObject
{
	public:

	UpgradeObject() = delete;
	UpgradeObject(Game* gamePtr);
	~UpgradeObject() = default;

	void handleInput(InputData& inputData);
	void update(float deltaTime);
    void render(sf::RenderTarget& target, sf::RenderStates& states);

	private:

	InfoBox	m_backgroundBox;
	Button m_plusButton;
	Button m_minusButton;


};