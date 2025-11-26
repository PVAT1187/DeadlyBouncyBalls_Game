#include "GamePlayScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

const int SURVIVAL_TIME_TEXT_SIZE = 25;

const float DEGREE = 90.f;

GamePlayScreen::GamePlayScreen(Game& game, RenderWindow& window) :
	Screen(game),
	game(game),
	window(window),
	player(window),
	ballManager(window),
	survivalClock(),
	survivalTimeText(Text(game.getFont(), "", SURVIVAL_TIME_TEXT_SIZE))
{
	window.setMouseCursorVisible(false);
	initSurvivalTimeText();
	survivalClock.restart();
}

void GamePlayScreen::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		player.rotate(DEGREE);
	}
}

void GamePlayScreen::update(float deltaTime)
{
	float survivalTime = survivalClock.getElapsedTime().asSeconds();
	survivalTimeText.setString("Survival Time: " +
		to_string(survivalTime) + "s");

	player.update(window);
	ballManager.update(deltaTime, window);

	if (ballManager.isGameOver(player))
	{
		game.switchToGameOverScreen(survivalTime);
		return;
	}
}

void GamePlayScreen::render(RenderWindow& window)
{
	player.draw(window);
	ballManager.draw(window);
	window.draw(survivalTimeText);
}

void GamePlayScreen::initSurvivalTimeText()
{
	survivalTimeText.setFillColor(Color::White);

	FloatRect survivalTimeTextBounds = survivalTimeText.getLocalBounds();
	survivalTimeText.setOrigin(survivalTimeTextBounds.size / 2.f);
	survivalTimeText.setPosition(Vector2f(0, 0));
}

