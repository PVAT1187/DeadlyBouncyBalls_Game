#ifndef GAME_H
#define GAME_H

#include "Screens/Screen.h"
#include "Entities/Player.h"
#include "Entities/Ball.h"

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

