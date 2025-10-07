#include "GameState.hpp"
#include "InfoBox.hpp"
#include "Vampire.h"
#include <SFML/Graphics.hpp>
#include <vector>

class VampireHandler;

class StartScreen : public GameState {

	public:
	
	StartScreen() = delete;
    StartScreen(Game* gamePtr);
	~StartScreen() = default;

    void handleInput(InputData& inputData) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target, sf::RenderStates& states) override;

	bool isReady() { return m_isReady; };
	void setIsReady(bool isReady) { m_isReady = isReady; };

	private:

    sf::Font* m_font;
    sf::Text m_welcomeText;
	bool m_isReady = false;

	std::unique_ptr<VampireHandler> m_pVampireHandler;
	InfoBox instructionBox;

};
