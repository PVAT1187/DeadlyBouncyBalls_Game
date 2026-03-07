#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Overlays/PauseMenu/PauseMenuOverlay.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

PauseMenuOverlay::PauseMenuOverlay( Game& game) :
	Overlay(game),
	pauseMenuTitle(Text(game.getAssets().getFont(), "GAME PAUSED", TITLE_TEXT_SIZE)),
	resumeButton("RESUME", game.getAssets().getFont(), BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getAssets().getFont(), BUTTON_SIZE, { 0, 0 }),
	selectedOption(PauseMenuOption::NONE)
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
		if (resumeButton.isClicked())
		{
			selectedOption = PauseMenuOption::RESUME;
		}
		else if (mainMenuButton.isClicked())
		{
			selectedOption = PauseMenuOption::MAIN_MENU;
		}
	}
}

void PauseMenuOverlay::update(float deltaTime,
	const InputState& inputState)
{
	resumeButton.update(inputState.mousePosition);
	mainMenuButton.update(inputState.mousePosition);
}

void PauseMenuOverlay::render()
{
	auto& renderer = game.getRenderer();
	
	renderer.draw(dimBackground);
	renderer.draw(pauseMenuTitle);
    resumeButton.draw(renderer);
    mainMenuButton.draw(renderer);
}

bool PauseMenuOverlay::hasSelectedOption() const
{
	return selectedOption != PauseMenuOption::NONE;
}

PauseMenuOption PauseMenuOverlay::getSelectedOption() const
{
	return selectedOption;
}

void PauseMenuOverlay::initPauseTitle()
{
	centerText(pauseMenuTitle, game.getRenderer().getWindowSize());
}

void PauseMenuOverlay::updateButtonPosition()
{
	vector<TextButton*> buttons = { &resumeButton, &mainMenuButton };
	positionButtons(pauseMenuTitle, buttons, 
		game.getRenderer().getWindowSize());
}
