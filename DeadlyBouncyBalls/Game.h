#ifndef GAME_H
#define GAME_H

#include "Screen.h"
#include "Player.h"
#include "Ball.h"

enum class ScreenType
{
	None,
	GameStart,
	GamePlay,
	GameOver
};

class Game
{
	public:
		Game();

		void run();

		void switchToGameStartScreen();
		void switchToGamePlayScreen();
		void switchToGameOverScreen(float survivalTime);

		sf::Font& getFont();

	private:
		sf::RenderWindow window;
		sf::Font font;

		std::unique_ptr<Screen> currentScreen;

		void initFont();
};

#endif // !GAME_H

