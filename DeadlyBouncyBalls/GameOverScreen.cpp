#include "GameOverScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

GameOverScreen::GameOverScreen(Game& game, RenderWindow& window, 
	float finalSurvivalTime) :
	Screen(game),
	game(game),
	window(window),
	gameOverText(Text(game.getFont(), "GAME OVER", 100)),
	finalSurvivalTimeText(Text(game.getFont(), "", 25))
{
	window.setMouseCursorVisible(true);
	
	initGameOverText();
	initFinalSurvivalTimeText(finalSurvivalTime);
}

void GameOverScreen::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>())
	{
		game.switchToGameStartScreen();
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
		centerPosition.x, centerPosition.y + 100.f));
}