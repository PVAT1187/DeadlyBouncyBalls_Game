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
			const InputState& inputState) override;
		void render() override;

	private:
		GameWorld gameWorld;

		sf::Text survivalTimeText;
		sf::Clock survivalClock;

		std::unique_ptr<PauseMenuOverlay> pauseOverlay;

		void initSurvivalTimeText();
		void updateSurvivalTimeText(float survivalTime);	
};

#endif // !GAME_PLAY_SCREEN_H

