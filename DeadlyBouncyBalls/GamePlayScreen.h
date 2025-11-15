#ifndef GAME_PLAY_SCREEN_H
#define GAME_PLAY_SCREEN_H

#include "Screen.h"
#include "Player.h"
#include "Ball.h"

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
		Ball ball;

		sf::Font font;

		sf::Clock survivalClock;
		sf::Text survivalTimeText;

		void initFont();
		void initSurvivalTimeText();
};

#endif // !GAME_PLAY_SCREEN_H

