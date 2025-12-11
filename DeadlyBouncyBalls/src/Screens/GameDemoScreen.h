#ifndef GAME_DEMO_SCREEN_H
#define GAME_DEMO_SCREEN_H

#include "Screens/Screen.h"
#include "Entities/BallManager.h"
#include "Overlays/InstructionOverlay.h"

class GameDemoScreen : public Screen
{
	public:
		GameDemoScreen(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		BallManager ballManager;

		bool instructionShown;

		std::unique_ptr<InstructionOverlay> instructionOverlay;
};

#endif // !GAME_DEMO_SCREEN_H

