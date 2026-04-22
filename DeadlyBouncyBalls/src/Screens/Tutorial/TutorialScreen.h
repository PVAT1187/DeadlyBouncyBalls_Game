#ifndef TUTORIAL_SCREEN_H
#define TUTORIAL_SCREEN_H

#include "Screens/Screen.h"
#include "Overlays/Tutorial/TutorialOverlay.h"

class TutorialScreen : public Screen
{
	public:
		TutorialScreen(Game& game);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime, 
			const Input& Input) override;
		void render() override;

	private:
		std::unique_ptr<TutorialOverlay> tutorialOverlay;
};

#endif // !GAME_DEMO_SCREEN_H

