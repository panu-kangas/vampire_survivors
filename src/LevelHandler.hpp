#pragma once

#include "DataStructs.hpp"
#include "GameState.hpp"
#include "UpgradeShop.hpp"
#include "Level.hpp"
#include "Projectile.hpp"
#include <array>
#include <memory>

class Game;
class Level;
struct InputData;

class LevelHandler
{
	public:

	LevelHandler() = delete;
	LevelHandler(Game* gamePtr);
	~LevelHandler() = default;

	void initNewLevel(unsigned int levelId);
	void update(float deltaTime, InputData& inputData);
    void render(sf::RenderTarget& target, sf::RenderStates& states);

	bool hasLevelStarted() { return m_curLevelPtr->hasLevelStarted(); };

	std::vector<Projectile>& getProjectileVec() { return m_curLevelPtr->getProjectileVec(); };

	private:

	std::array<LevelData, 7> m_levelArr = {{
		{1, {10, 0, 0, 0, 1.2f}},
		{2, {16, 0, 0, 0, 1.0f}},
		{3, {14, 6, 0, 0, 1.0f}},
		{4, {18, 8, 4, 0, 1.0f}},
		{5, {22, 11, 8, 0, 0.9f}},
		{6, {26, 15, 12, 0, 0.9f}},
	}};
	std::unique_ptr<Level> m_curLevelPtr;
	std::unique_ptr<UpgradeShop> m_pUpgradeShop;
	unsigned int m_curLevelId = 1;
	bool m_isShopActive = true;
	Game* m_pGame;

};
