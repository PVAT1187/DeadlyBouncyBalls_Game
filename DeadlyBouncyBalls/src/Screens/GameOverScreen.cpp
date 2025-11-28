#include "Screens/GameOverScreen.h"
#include "UI/UIUtils.h"
#include "Core/Game.h"

#include <iostream>

using namespace sf;
using namespace std;
using namespace UIUtils;

GameOverScreen::GameOverScreen(Game& game, RenderWindow& window, 
	float finalSurvivalTime) :
	Screen(game, window),
	gameOverText(Text(game.getFont(), "GAME OVER", Screen::TITLE_TEXT_SIZE)),
	finalSurvivalTimeText(Text(game.getFont(), "", Screen::BODY_TEXT_SIZE)),
	playAgainButton("PLAY AGAIN", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 })
{
	this->window.setMouseCursorVisible(true);
	
	initGameOverText();
	initFinalSurvivalTimeText(finalSurvivalTime);
	updateButtonPosition();
}

void GameOverScreen::handleEvent(const Event& event) 
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		if (playAgainButton.isClicked(window))
		{
			game.switchToGamePlayScreen();
		}
		else if (mainMenuButton.isClicked(window))
		{
			game.switchToGameStartScreen();
		}
	}
}

void GameOverScreen::update(float deltaTime) 
{
	playAgainButton.update(window);
	mainMenuButton.update(window);	
}

void GameOverScreen::render(RenderWindow& window)
{
	window.draw(gameOverText);
	window.draw(finalSurvivalTimeText);
	playAgainButton.draw(window);
	mainMenuButton.draw(window);
}

void GameOverScreen::initGameOverText()
{
	centerTitleText(gameOverText, window);
}

void GameOverScreen::initFinalSurvivalTimeText(float finalSurvivalTime)
{
	finalSurvivalTimeText.setString("Survived: " + 
		to_string(finalSurvivalTime) + "s");
	centerBodyText(finalSurvivalTimeText, window, Screen::TEXT_SPACING);
}

void GameOverScreen::updateButtonPosition()
{
	vector<TextButton*> buttons = { &playAgainButton, &mainMenuButton };
	positionButtons(gameOverText, buttons, window);
} 