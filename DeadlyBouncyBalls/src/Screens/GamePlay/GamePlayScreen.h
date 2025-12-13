#ifndef GAME_PLAY_SCREEN_H
#define GAME_PLAY_SCREEN_H

#include "Screens/Screen.h"
#include "Overlays/PauseMenu/PauseMenuOverlay.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"

#include <vector>

class GamePlayScreen : public Screen
{
	public:
		GamePlayScreen(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

		void unpause();

	private:
		Player player;
		BallManager ballManager;

		sf::Clock survivalClock;
		sf::Text survivalTimeText;

		bool paused;
		std::unique_ptr<PauseMenuOverlay> pauseOverlay;

		void initSurvivalTimeText();
		void updateSurvivalTimeText(float survivalTime);
		void positionPlayer();
};

#endif // !GAME_PLAY_SCREEN_H

