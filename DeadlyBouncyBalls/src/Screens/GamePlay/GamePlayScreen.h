#ifndef GAME_PLAY_SCREEN_H
#define GAME_PLAY_SCREEN_H

#include "Screens/Screen.h"
#include "Overlays/PauseMenu/PauseMenuOverlay.h"
#include "Core/World/GameWorld/GameWorld.h"

class GamePlayScreen : public Screen
{
	public:
		GamePlayScreen(Game& game);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime,
			const Input& Input) override;
		void render() override;

	private:
		GameWorld gameWorld;

		sf::Text survivalTimeText;
		sf::Text scoreText;

		sf::Clock survivalClock;

		std::unique_ptr<PauseMenuOverlay> pauseOverlay;

		void initText();
		void updateText(float survivalTime, int score);	
};

#endif // !GAME_PLAY_SCREEN_H

