#pragma once

#include "DataStructs.hpp"
#include "GameState.hpp"
#include "VampireHandler.hpp"
#include "VampireInfoBox.hpp"
#include "InfoBox.hpp"
#include "Projectile.hpp"
#include "WeaponInfoBox.hpp"
#include <memory>

class Game;

class Level : public GameState
{
	public:

	Level() = delete;
	Level(Game* gamePtr, unsigned int levelId, VampireLevelData& vampireData);
	~Level() = default;

	void handleInput(InputData& inputData) override;
	void update(float deltaTime) override;
    void render(sf::RenderTarget& target, sf::RenderStates& states) override;
	void renderIntroScreen(sf::RenderTarget& target, sf::RenderStates& states);
	void updateInfoBoxes(float deltaTime);

	void handleProjectiles(Player* player, float deltaTime);

	bool isLevelReady() const { return m_isReady; };
	bool hasLevelStarted() const { return m_levelCanStart; };

	std::vector<Projectile>& getProjectileVec() { return m_projectileVec; };

	private:

//	void drawHealthIcons(sf::RenderTarget &target, sf::RenderStates states);

	bool m_levelCanStart = false;
	bool m_isLevelPassed = false;
	bool m_isReady = false;
	unsigned int m_levelId;
	VampireLevelData m_vampireData;
	std::unique_ptr<VampireHandler> m_vampireHandler;

	InfoBox m_scoreInfo;
	InfoBox m_healthBox;
	VampireInfoBox m_vampireInfoBox;
	WeaponInfoBox m_weaponInfoBox;
	sf::RectangleShape m_healthIcon;

	std::vector<Projectile> m_projectileVec;

};