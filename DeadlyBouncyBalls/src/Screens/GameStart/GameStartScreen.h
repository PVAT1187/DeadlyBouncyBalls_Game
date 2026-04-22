#ifndef GAME_START_SCREEN_H
#define	GAME_START_SCREEN_H

#include "Screens/Screen.h"
#include "UI/Buttons/TextButton.h"

class GameStartScreen : public Screen
{
	public:
		GameStartScreen(Game& game);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime,
			const Input& Input) override;
		void render() override;

	private:
		sf::Text gameTitleText;

		TextButton playButton;
		TextButton quitButton;

		void initGameTitleText();
		void updateButtonPosition();
};

#endif // !GAME_START_SCREEN_H
