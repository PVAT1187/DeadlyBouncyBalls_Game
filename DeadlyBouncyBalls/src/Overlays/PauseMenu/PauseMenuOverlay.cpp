#include "Config/GameConfig.h"
#include "Core/App/Game.h"
#include "Core/Input/Input.h"
#include "Overlays/PauseMenu/PauseMenuOverlay.h"
#include "Utilities/UI/UIUtils.h"

PauseMenuOverlay::PauseMenuOverlay( Game& game) :
	Overlay(game),
	pauseMenuTitle(sf::Text(game.getAssets().getFont(), "GAME PAUSED", Config::UI::TITLE_TEXT_SIZE)),
	resumeButton("RESUME", game.getAssets().getFont(), Config::Button::BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getAssets().getFont(), Config::Button::BUTTON_SIZE, { 0, 0 }),
	selectedOption(PauseMenuOption::NONE)
{
	initDimBackground();
	initPauseTitle();
	updateButtonPosition();
}

void PauseMenuOverlay::handleEvent(const sf::Event& event)
{
	if (event.is<sf::Event::MouseButtonPressed>() &&
		event.getIf<sf::Event::MouseButtonPressed>()->button == 
		sf::Mouse::Button::Left)
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

void PauseMenuOverlay::update(
	float deltaTime,
	const Input& Input)
{
	resumeButton.update(Input.mousePosition);
	mainMenuButton.update(Input.mousePosition);
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
	UIUtils::centerText(
		pauseMenuTitle, 
		game.getRenderer().getWindowSize()
	);
}

void PauseMenuOverlay::updateButtonPosition()
{
	std::vector<TextButton*> buttons = { 
		&resumeButton, 
		&mainMenuButton 
	};

	UIUtils::positionButtons(
		pauseMenuTitle, 
		buttons,
		game.getRenderer().getWindowSize()
	);
}
