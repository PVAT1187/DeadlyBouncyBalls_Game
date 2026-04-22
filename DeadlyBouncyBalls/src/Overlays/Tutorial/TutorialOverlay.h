#ifndef TUTORIAL_OVERLAY_H
#define	TUTORIAL_OVERLAY_H

#include "Overlays/Overlay.h"
#include "UI/Buttons/TextButton.h"

class TutorialOverlay : public Overlay
{
	public:
		TutorialOverlay(Game& game);

		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime,
			const Input& Input) override;
		void render() override;

		bool isFinished() const;

	private:
		sf::Text tutorialOverlayTitle;
		std::vector<sf::Text> instructions;

		TextButton continueButton;

		bool finished;

		void initTutorialOverlayTitle();
		void initInstructions();
		void updateButtonPosition();
};

#endif // !TUTORIAL_OVERLAY_H