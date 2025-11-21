#ifndef GAME_PLAY_SCREEN_H
#define GAME_PLAY_SCREEN_H

#include "Screen.h"
#include "Player.h"
#include "Ball.h"

#include <vector>

class Game;

class GamePlayScreen : public Screen
{
	public:
		GamePlayScreen(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		Game& game;
		sf::RenderWindow& window; 

		Player player;
		std::vector<Ball> balls;

		sf::Clock survivalClock;
		sf::Text survivalTimeText;

		void initSurvivalTimeText();

		void spawnBall(float radius, sf::Vector2f position, 
			sf::Vector2f velocity);

		void resolveBallCollisions();
};

#endif // !GAME_PLAY_SCREEN_H

