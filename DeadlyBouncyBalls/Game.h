#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Ball.h"

class Game
{
	public:
		Game();
		void run();

	private:
		sf::RenderWindow window;
		Player player;
		Ball ball;

		bool isGameOver;
		sf::Font font;
		sf::Text gameOverText;

		void processEvents();
		void update(float deltaTime);
		void render();
};

#endif // !GAME_H

