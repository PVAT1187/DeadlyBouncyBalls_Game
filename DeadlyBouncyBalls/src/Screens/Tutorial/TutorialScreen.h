#ifndef TUTORIAL_SCREEN_H
#define TUTORIAL_SCREEN_H

#include "Core/World/WorldBounds.h"
#include "Core/Systems/Boundary/BoundarySystem.h"
#include "Screens/Screen.h"
#include "Overlays/Tutorial/TutorialOverlay.h"
#include "Entities/Enemies/BallManager.h"

class TutorialScreen : public Screen
{
	public:
		TutorialScreen(Game& game);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime, 
			const InputState& inputState) override;
		void render() override;

	private:
		WorldBounds worldBounds;
		BoundarySystem boundarySystem;

		BallManager ballManager;

		std::unique_ptr<TutorialOverlay> tutorialOverlay;
};

#endif // !GAME_DEMO_SCREEN_H

