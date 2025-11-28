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

		template<typename ScreenType, typename... Arguments>
		void switchScreen(Arguments&&... arguments);

		const sf::Font& getFont() const;

	private:
		sf::RenderWindow window;

		sf::Font font;

		std::unique_ptr<Screen> currentScreen;

		void initFont();
};

#include "Core/Game.inl"
#endif // !GAME_H

