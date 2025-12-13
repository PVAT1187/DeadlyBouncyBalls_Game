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

		const sf::Texture& getPlayerTexture() const;
		const sf::Texture& getAimingIconTexture() const;
		const sf::Texture& getBulletIconTexture() const;

	private:
		sf::RenderWindow window;

		sf::Font font;

		sf::Texture playerTexture;
		sf::Texture aimingIconTexture;
		sf::Texture bulletIconTexture;

		std::unique_ptr<Screen> currentScreen;

		void initFont();
		void initTexture();
};

#include "Core/Game.inl"
#endif // !GAME_H

