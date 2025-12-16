#include "Config/Constants/GameConstants.h"
#include "Core/Application/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"
#include "Utilities/UI/UIUtils.h"

#include <iostream>

using namespace sf;
using namespace std;
using namespace UIUtils;

GameOverScreen::GameOverScreen(Game& game, RenderWindow& window, 
	float finalSurvivalTime) :
	Screen(game, window),
	gameOverText(Text(game.getFont(), "GAME OVER", TITLE_TEXT_SIZE)),
	finalSurvivalTimeText(Text(game.getFont(), "", BODY_TEXT_SIZE)),
	playAgainButton("PLAY AGAIN", game.getFont(), BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getFont(), BUTTON_SIZE, { 0, 0 })
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
			game.switchScreen<GamePlayScreen>(window);
		}
		else if (mainMenuButton.isClicked(window))
		{
			game.switchScreen<GameStartScreen>(window);
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
	centerBodyText(finalSurvivalTimeText, window, TEXT_SPACING);
}

void GameOverScreen::updateButtonPosition()
{
	vector<TextButton*> buttons = { &playAgainButton, &mainMenuButton };
	positionButtons(gameOverText, buttons, window);
} 