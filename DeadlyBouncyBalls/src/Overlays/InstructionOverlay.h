#ifndef INSTRUCTION_OVERLAY_H
#define	INSTRUCTION_OVERLAY_H

#include "Overlays/Overlay.h"
#include "UI/TextButton.h"

class InstructionOverlay : public Overlay
{
	public:
		InstructionOverlay(Game& game, sf::RenderWindow& window);

		void handleEvent(const sf::Event& event) override;
		void update() override;
		void render(sf::RenderWindow& window) override;

	private:
		sf::Text instructionOverlayTitle;
		sf::Text instructions;

		TextButton continueButton;

		void initInstructionOverlayTitle();
		void initInstructionText();
		void updateButtonPosition();
};

#endif // ! INSTRUCTION_OVERLAY_H

