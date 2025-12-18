#ifndef GAME_H
#define GAME_H

#include "Core/Assets/GameAssets.h"  
#include "Screens/Screen.h"

class Game
{
	public:
		Game();

		void run();

		template<typename ScreenType, typename... Arguments>
		void switchScreen(Arguments&&... arguments);

		const GameAssets& getAssets() const;

	private:
		sf::RenderWindow window;
		GameAssets assets;

		std::unique_ptr<Screen> currentScreen;
};

#include "Core/App/Game.inl"
#endif // !GAME_H

