#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Vampire;
class Game;

class VampireHandler
{
	public:

	VampireHandler() = delete;
	VampireHandler(Game* pGame, sf::Texture& vampTexture);
	~VampireHandler() = default;

	float	getNextVampireCooldown() { return m_nextVampireCooldown; }
	void 	vampireSpawner(float deltaTime);
	void	StartScreenVampireSpawner(float deltaTime);
	void 	initVampires();
	void 	update(float deltaTime, Game::State gameState);
	void	drawVampires(sf::RenderTarget &target, sf::RenderStates states);
	std::vector<std::unique_ptr<Vampire>>& getVampires() { return m_pVampires; };

	private:

	float m_vampireCooldown = 0.0f;
    float m_nextVampireCooldown = 2.0f;
    int m_spawnCount = 0;

	std::vector<std::unique_ptr<Vampire>> m_pVampires;

	Game* m_pGame;
	sf::Texture& m_vampTexture;


};