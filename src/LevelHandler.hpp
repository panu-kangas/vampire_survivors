#pragma once

#include "DataStructs.hpp"
#include "GameState.hpp"
#include "Level.hpp"
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



	private:

	std::array<LevelData, 7> m_levelArr = {{
		{1, {10, 10, 0, 0, 1.0f}},
		{2, {25, 0, 0, 0, 0.8f}},
		{3, {30, 10, 0, 0, 0.8f}},
		{4, {40, 15, 10, 0, 0.7f}},
		{5, {50, 25, 10, 0, 0.6f}},
		{6, {50, 40, 20, 1, 0.8f}},
	}};
	std::unique_ptr<Level> m_curLevelPtr;
	unsigned int m_curLevelId = 1;
	Game* m_pGame;

};