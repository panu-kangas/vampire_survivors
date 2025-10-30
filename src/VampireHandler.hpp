#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Vampire.h"
#include "DataStructs.hpp"

class Game;

class VampireHandler
{
	public:

	VampireHandler() = delete;
	VampireHandler(Game* pGame, sf::Texture& vampTexture, float vampireSpawnRate);
	~VampireHandler() = default;

	void 	vampireSpawner(float deltaTime, VampireLevelData& vampireData);
	void	StartScreenVampireSpawner(float deltaTime);
	void 	update(float deltaTime, Game::State gameState);
	void	drawVampires(sf::RenderTarget &target, sf::RenderStates states);
	std::vector<std::unique_ptr<Vampire>>& getVampires() { return m_pVampires; };

	bool isVampireVecEmpty() const { return m_pVampires.empty(); };

	private:

	VampireTypes getVampireType(VampireLevelData& vampireData);
	void addVampireToVec(sf::Vector2f& position, VampireTypes& type, VampireLevelData& vampireData);

	float m_vampireCooldown;
	float m_nextVampireCooldown;

	std::vector<std::unique_ptr<Vampire>> m_pVampires;

	Game* m_pGame;
	sf::Texture& m_vampTexture;


};