#include "GameOverScreen.h"
#include "UIUtils.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;
using namespace UIUtils;

const float TEXT_SPACING = 125.f;

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
	colorAndCenterText(gameOverText, window);
}

void GameOverScreen::initFinalSurvivalTimeText(float finalSurvivalTime)
{
	finalSurvivalTimeText.setString("Survived: " + 
		to_string(finalSurvivalTime) + "s");
	finalSurvivalTimeText.setFillColor(Color::White);

	Vector2f centerPosition = static_cast<Vector2f>
		(window.getSize()) / 2.f;
	FloatRect survivalTimeTextBounds = finalSurvivalTimeText.getLocalBounds();
	finalSurvivalTimeText.setOrigin(survivalTimeTextBounds.size / 2.f);
	finalSurvivalTimeText.setPosition(Vector2f(
		centerPosition.x, centerPosition.y + TEXT_SPACING));
}

void GameOverScreen::updateButtonPosition()
{
	vector<TextButton*> buttons = { &playAgainButton, &mainMenuButton };
	positionButtons(gameOverText, buttons, window);
} 