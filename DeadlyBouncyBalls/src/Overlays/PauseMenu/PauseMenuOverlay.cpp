#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Overlays/PauseMenu/PauseMenuOverlay.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

PauseMenuOverlay::PauseMenuOverlay(GamePlayScreen& gamePlayScreen, 
	Game& game, RenderWindow& window) :
	Overlay(game, window, &game.getAssets()),
	gamePlayScreen(gamePlayScreen),
	pauseMenuTitle(Text(assets->getFont(), "GAME PAUSED", TITLE_TEXT_SIZE)),
	resumeButton("RESUME", assets->getFont(), BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", assets->getFont(), BUTTON_SIZE, { 0, 0 })
{
	initDimBackground();
	initPauseTitle();
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
			game.switchScreen<GameStartScreen>(window);
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
