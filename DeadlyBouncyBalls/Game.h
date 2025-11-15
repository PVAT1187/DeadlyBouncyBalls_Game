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

	private:
		sf::RenderWindow window;

		std::unique_ptr<Screen> currentScreen;
};

#endif // !GAME_H

