#include "PauseMenuOverlay.h"
#include "UIUtils.h"
#include "Game.h"
#include "GamePlayScreen.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

PauseMenuOverlay::PauseMenuOverlay(GamePlayScreen& gamePlayScreen, Game& game, RenderWindow& window) :
	Overlay(game, window),
	gamePlayScreen(gamePlayScreen),
	pauseMenuTitle(Text(game.getFont(), "GAME PAUSED", Screen::TITLE_TEXT_SIZE)),
	resumeButton("RESUME", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 })
{
	initPauseTitle();
	initDimBackground();
	updateButtonPosition();
}

void PauseMenuOverlay::handleEvent(const Event& event) 
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		if (resumeButton.isClicked(window))
		{
			gamePlayScreen.unpause();
		}
		else if (mainMenuButton.isClicked(window))
		{
			game.switchToGameStartScreen();
		}
	}
}

void PauseMenuOverlay::update() 
{
	resumeButton.update(window);
	mainMenuButton.update(window);
}

void PauseMenuOverlay::render(RenderWindow& window)
{
    window.draw(dimBackground);
	window.draw(pauseMenuTitle);
    resumeButton.draw(window);
    mainMenuButton.draw(window);
}

void PauseMenuOverlay::initPauseTitle()
{
	centerTitleText(pauseMenuTitle, window);
}

void PauseMenuOverlay::updateButtonPosition()
{
	vector<TextButton*> buttons = { &resumeButton, &mainMenuButton };
	positionButtons(pauseMenuTitle, buttons, window);
}
