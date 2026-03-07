#ifndef PAUSE_MENU_OVERLAY_H
#define PAUSE_MENU_OVERLAY_H

#include "Overlays/Overlay.h"
#include "UI/Buttons/TextButton.h"

enum class PauseMenuOption
{
	NONE,
	RESUME,
	MAIN_MENU
};

class PauseMenuOverlay : public Overlay
{
	public:
		PauseMenuOverlay(Game& game);
		
		void handleEvent(const sf::Event& event) override;
		void update(float deltaTime,
			const InputState& inputState) override;
		void render() override;

		bool hasSelectedOption() const;
		PauseMenuOption getSelectedOption() const;

	private:
		sf::Text pauseMenuTitle;

		TextButton resumeButton;
		TextButton mainMenuButton;

		PauseMenuOption selectedOption;

		void initPauseTitle();
		void updateButtonPosition();
};

#endif // !PAUSE_MENU_OVERLAY_H
