#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screens/Screen.h"
#include "UI/Buttons/TextButton.h"

class GameOverScreen : public Screen
{
	public:
		GameOverScreen(Game& game,
			float finalSurvivalTime,
			int score);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime,
			const Input& Input) override;
		void render() override;

	private:
		sf::Text gameOverText;
		sf::Text finalSurvivalTimeText;
		sf::Text scoreText;

		TextButton playAgainButton;
		TextButton mainMenuButton;

		void initText(float finalSurvivalTime, int score);
		void updateButtonPosition();
};

#endif // !GAME_OVER_SCREEN_H
