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

		void switchToGameStartScreen();
		void switchToGameDemoScreen();
		void switchToGamePlayScreen();
		void switchToGameOverScreen(float survivalTime);

		const sf::Font& getFont() const;
		const sf::Color& getTextColor() const;

	private:
		sf::RenderWindow window;

		sf::Font font;
		sf::Color textColor;

		std::unique_ptr<Screen> currentScreen;

		void initFont();
		void initTextColor();
};

#endif // !GAME_H

