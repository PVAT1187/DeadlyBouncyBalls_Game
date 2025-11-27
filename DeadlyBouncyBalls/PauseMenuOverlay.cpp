#include "PauseMenuOverlay.h"
#include "UIUtils.h"
#include "Game.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

PauseMenuOverlay::PauseMenuOverlay(Game& game, RenderWindow& window) : 
	Overlay(game, window),
	active(false),
	pauseMenuTitle(Text(game.getFont(), "GAME PAUSED", Screen::TITLE_TEXT_SIZE)),
	resumeButton("RESUME", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 })
{
	initPauseTitle();
	initDimBackground();
	updateButtonPosition();
}

void PauseMenuOverlay::activate()
{
	active = true;
}

void PauseMenuOverlay::deactivate()
{
	active = false;
}

bool PauseMenuOverlay::isActive() const
{
	return active;
}

void PauseMenuOverlay::handleEvent(const Event& event) 
{
	if (!active)
		return;

	resumeButton.update(window);
	mainMenuButton.update(window);

	if (resumeButton.isClicked(window))
	{
		deactivate();
		game.switchToGamePlayScreen();
	}
	else if (mainMenuButton.isClicked(window))
	{
		deactivate();
		game.switchToGameStartScreen();
	}
}

void PauseMenuOverlay::update(float deltaTime) {}

void PauseMenuOverlay::render(RenderWindow& window)
{
    window.draw(dimBackground);
	window.draw(pauseMenuTitle);
    resumeButton.draw(window);
    mainMenuButton.draw(window);
}

void PauseMenuOverlay::initPauseTitle()
{
	colorAndCenterText(pauseMenuTitle, window);
}

void PauseMenuOverlay::updateButtonPosition()
{
	vector<TextButton*> buttons = { &resumeButton, &mainMenuButton };
	positionButtons(pauseMenuTitle, buttons, window);
}
