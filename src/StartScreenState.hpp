#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class StartScreen : public GameState {

	public:
	
	StartScreen() = delete;
    StartScreen(Game* gamePtr);

    void handleInput(InputData inputData) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;

	bool isReady() { return m_isReady; };

	private:

    sf::Font* m_font;
    sf::Text m_welcomeText;
	bool m_isReady = false;
};
