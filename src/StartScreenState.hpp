#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class StartScreen : public GameState {

	public:
	
	StartScreen() = delete;
    StartScreen(Game* gamePtr);

    void handleInput(sf::RenderTarget& target) override;

    void update(float deltaTime) override;

    void render(sf::RenderTarget& target) override;

	private:

    sf::Font* m_font;
    sf::Text m_welcomeText;
};
