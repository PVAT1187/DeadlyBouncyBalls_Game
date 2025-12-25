#ifndef TUTORIAL_OVERLAY_H
#define	TUTORIAL_OVERLAY_H

#include "Overlays/Overlay.h"
#include "UI/Buttons/TextButton.h"

class TutorialOverlay : public Overlay
{
public:
	TutorialOverlay(Game& game, sf::RenderWindow& window);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Text tutorialOverlayTitle;
	std::vector<Text> instructions;

	TextButton continueButton;

	void initTutorialOverlayTitle();
	void initInstructions();
	void updateButtonPosition();
};

#endif // !TUTORIAL_OVERLAY_H