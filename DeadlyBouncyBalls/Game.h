#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Ball.h"

#include <SFML/Graphics.hpp>

enum class GameState { Playing, GameOver };

const VideoMode DESKTOP_MODE = VideoMode::getDesktopMode();

class Game
{
	public:
		Game();
		void run();

	private:
		sf::RenderWindow window;
		Player player;
		Ball ball;
		GameState currentGameState;
};

#endif // !GAME_H

