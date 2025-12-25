#ifndef TUTORIAL_SCREEN_H
#define TUTORIAL_SCREEN_H

#include "Screens/Screen.h"
#include "Overlays/Tutorial/TutorialOverlay.h"
#include "Entities/Enemies/BallManager.h"

#include <vector>

class TutorialScreen : public Screen
{
	public:
		TutorialScreen(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime) override;
		void render(sf::RenderWindow& window) override;

	private:
		BallManager ballManager;

		bool instructionShown;

		std::unique_ptr<TutorialOverlay> tutorialOverlay;
};

#endif // !GAME_DEMO_SCREEN_H

