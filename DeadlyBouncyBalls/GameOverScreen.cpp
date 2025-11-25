#include "GameOverScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

const int GAME_OVER_TEXT_SIZE = 100;
const int FINAL_SURVIVAL_TIME_TEXT_SIZE = 25;

const float AMOUNT_Y_COORDINATE_INCREASED_BY = 100.f;

GameOverScreen::GameOverScreen(Game& game, RenderWindow& window, 
	float finalSurvivalTime) :
	Screen(game),
	game(game),
	window(window),
	gameOverText(Text(game.getFont(), "GAME OVER", GAME_OVER_TEXT_SIZE)),
	finalSurvivalTimeText(Text(game.getFont(), "", FINAL_SURVIVAL_TIME_TEXT_SIZE))
{
	window.setMouseCursorVisible(true);
	
	initGameOverText();
	initFinalSurvivalTimeText(finalSurvivalTime);
}

void GameOverScreen::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>())
	{
		game.switchToGamePlayScreen();
	}
}

void GameOverScreen::update(float deltaTime) {}

void GameOverScreen::render(RenderWindow& window)
{
	window.draw(gameOverText);
	window.draw(finalSurvivalTimeText);
}

void GameOverScreen::initGameOverText()
{
	gameOverText.setFillColor(Color::White);

	FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
	gameOverText.setOrigin(gameOverTextBounds.size / 2.f);
	gameOverText.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
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
		centerPosition.x, centerPosition.y + AMOUNT_Y_COORDINATE_INCREASED_BY));
}