#pragma once

#include "Button.hpp"
#include "GameState.hpp"
#include "VampireInfoBox.hpp"
#include "InfoBox.hpp"
#include "UpgradeObject.hpp"

class Game;

class UpgradeShop : public GameState
{
	public:

	UpgradeShop() = delete;
	UpgradeShop(Game* gamePtr, VampireLevelData& vampireData);
	~UpgradeShop() = default;

	void handleInput(InputData& inputData) override;
	void update(float deltaTime) override;
    void render(sf::RenderTarget& target, sf::RenderStates& states) override;

	void initShop();
	bool isReady() { return m_isReady; };

	private:

	bool m_isReady = false;
	bool m_displayWarning = false;
	VampireInfoBox m_vampireInfoBox;
	InfoBox m_skillPointInfoBox;

	std::vector<std::unique_ptr<UpgradeObject>> m_upgradeObjectVec;
	size_t m_activeObjIndex = 0;

	Button m_continueButton;
	sf::Text m_warningText;
};