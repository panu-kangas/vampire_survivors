#pragma once

struct VampireLevelData
{
	unsigned int whiteVampireCount;
	unsigned int redVampireCount;
	unsigned int greenVampireCount;
	unsigned int bossVampireCount;
	float vampireSpawnRate;
};

struct LevelData
{
	unsigned int levelId;
	VampireLevelData vampireData;
};