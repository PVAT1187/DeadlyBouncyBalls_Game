#ifndef GAME_START_SCREEN
#define	GAME_START_SCREEN

#include "Screen.h"

class Game;

class GameStartScreen : public Screen
{
	public:
		GameStartScreen(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		Game& game;
		sf::RenderWindow& window;

		sf::Text gameTitleText;
		sf::Text gameInstructionText;

		void initGameTilteText();
		void initGameInstructionText();
};

#endif // !GAME_START_SCREEN
