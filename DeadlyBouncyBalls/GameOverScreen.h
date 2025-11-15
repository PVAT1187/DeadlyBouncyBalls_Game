#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screen.h"

class Game;

class GameOverScreen : public Screen
{
	public:
		GameOverScreen(Game& game, sf::RenderWindow& window, 
			float finalSurvivalTime);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		Game& game;
		sf::RenderWindow& window;

		sf::Font font;
		sf::Text gameOverText;
		sf::Text finalSurvivalTimeText;

		void initFont();
		void initGameOverText();
		void initFinalSurvivalTimeText(float finalSurvivalTime);
};

#endif // !GAME_OVER_SCREEN_H

