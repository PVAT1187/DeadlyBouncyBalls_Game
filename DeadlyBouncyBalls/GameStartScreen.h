#ifndef GAME_START_SCREEN_H
#define	GAME_START_SCREEN_H

#include "Screen.h"
#include "TextButton.h"

class GameStartScreen : public Screen
{
	public:
		GameStartScreen(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		sf::Text gameTitleText;

		TextButton playButton;
		TextButton quitButton;

		void initGameTilteText();
		void updateButtonPositon();
};

#endif // !GAME_START_SCREEN_H
