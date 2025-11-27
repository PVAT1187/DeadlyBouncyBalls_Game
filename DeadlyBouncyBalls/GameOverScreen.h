#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screen.h"
#include "TextButton.h"

class GameOverScreen : public Screen
{
	public:
		GameOverScreen(Game& game, sf::RenderWindow& window, 
			float finalSurvivalTime);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		sf::Text gameOverText;
		sf::Text finalSurvivalTimeText;

		TextButton playAgainButton;
		TextButton mainMenuButton;

		void initGameOverText();
		void initFinalSurvivalTimeText(float finalSurvivalTime);
		void updateButtonPosition();
};

#endif // !GAME_OVER_SCREEN_H
