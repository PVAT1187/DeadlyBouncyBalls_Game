#ifndef GAME_PLAY_SCREEN_H
#define GAME_PLAY_SCREEN_H

#include "Screen.h"
#include "Player.h"
#include "BallManager.h"
#include "PauseMenuOverlay.h"

#include <vector>

class GamePlayScreen : public Screen
{
	public:
		GamePlayScreen(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		Player player;
		BallManager ballManager;

		sf::Clock survivalClock;
		sf::Text survivalTimeText;

		bool paused;
		sf::Time pausedAt;
		sf::Time pausedDuration;
		std::unique_ptr<PauseMenuOverlay> pauseOverlay;

		void initSurvivalTimeText();
};

#endif // !GAME_PLAY_SCREEN_H

