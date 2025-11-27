#ifndef PAUSE_MENU_OVERLAY_H
#define PAUSE_MENU_OVERLAY_H

#include "Overlay.h"
#include "TextButton.h"

#include <SFML/Graphics.hpp>

class PauseMenuOverlay : public Overlay
{
	public:
		PauseMenuOverlay(Game& game, sf::RenderWindow& window);
		
		void handleEvent(const sf::Event& event) override;
		void update() override;
		void render(sf::RenderWindow& window) override;
	
	private:
		sf::Text pauseMenuTitle;

		TextButton resumeButton;
		TextButton mainMenuButton;

		void initPauseTitle();
		void updateButtonPosition();
};

#endif // PAUSE_MENU_OVERLAY_H
