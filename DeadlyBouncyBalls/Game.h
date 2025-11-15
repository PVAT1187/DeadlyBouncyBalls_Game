#ifndef GAME_H
#define GAME_H

#include "Screen.h"
#include "Player.h"
#include "Ball.h"

class Game
{
	public:
		Game();

		void run();

		void switchToGamePlayScreen();
		void switchToGameOverScreen(float finalSurvivalTime);
		void switchToGameStartScreen();

		sf::Font& getFont() { return font; }

	private:
		sf::RenderWindow window;
		sf::Font font;

		std::unique_ptr<Screen> currentScreen;

		void initFont();
};

#endif // !GAME_H

