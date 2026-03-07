#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screens/Screen.h"
#include "UI/Buttons/TextButton.h"

class GameOverScreen : public Screen
{
	public:
		GameOverScreen(Game& game, float finalSurvivalTime);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime,
			const InputState& inputState) override;
		void render() override;

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
