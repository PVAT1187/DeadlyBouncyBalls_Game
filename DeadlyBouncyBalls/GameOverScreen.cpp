#include "GameOverScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

GameOverScreen::GameOverScreen(Game& game, RenderWindow& window, 
	float finalSurvivalTime) :
	game(game),
	window(window),
	font(),
	gameOverText(Text(font, "GAME OVER", 60)),
	finalSurvivalTimeText(Text(font, "", 25))
{
	initFont();
	initGameOverText();
	initFinalSurvivalTimeText(finalSurvivalTime);
}

void GameOverScreen::handleEvent(const sf::Event& event)
{
	if (event.is<Event::MouseButtonPressed>())
	{
		game.switchToGamePlayScreen();
	}
}

void GameOverScreen::update(float deltaTime) {}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(gameOverText);
	window.draw(finalSurvivalTimeText);
}

void GameOverScreen::initFont()
{
	if (!font.openFromFile("C:/Users/pvat2/source/Personal Projects/DeadlyBouncyBalls/assets/fonts/arial.ttf"))
	{
		cerr << "Failed to load font!" << endl;
	}
}

void GameOverScreen::initGameOverText()
{
	gameOverText.setFont(font);
	gameOverText.setFillColor(Color::White);

	FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
	gameOverText.setOrigin(gameOverTextBounds.size / 2.f);
	gameOverText.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
}

void GameOverScreen::initFinalSurvivalTimeText(float finalSurvivalTime)
{
	finalSurvivalTimeText.setString("Final Survival Time: " +
		to_string(finalSurvivalTime) + "s");
	finalSurvivalTimeText.setFont(font);
	finalSurvivalTimeText.setFillColor(Color::White);

	Vector2f centerPosition = static_cast<Vector2f>
		(window.getSize()) / 2.f;
	FloatRect survivalTimeTextBounds = finalSurvivalTimeText.getLocalBounds();
	finalSurvivalTimeText.setOrigin(survivalTimeTextBounds.size / 2.f);
	finalSurvivalTimeText.setPosition(Vector2f(
		centerPosition.x, centerPosition.y + 70.f));
}