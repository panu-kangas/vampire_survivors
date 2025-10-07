#include "GameState.hpp"
#include <SFML/Graphics.hpp>


class EndScreen : public GameState {

	public:
	
	EndScreen() = delete;
    EndScreen(Game* gamePtr);
	~EndScreen() = default;

    void handleInput(InputData& inputData) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target, sf::RenderStates& states) override;

	bool isReady() { return m_isReady; };
	void setIsReady(bool ready) { m_isReady = ready; };

	private:

    sf::Font* m_font;
    sf::Text m_welcomeText;
	bool m_isReady = false;

};