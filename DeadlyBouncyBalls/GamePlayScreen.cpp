#include "GamePlayScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

GamePlayScreen::GamePlayScreen(Game& game, RenderWindow& window) :
	Screen(game),
	game(game),
	window(window),
	player(window),
	survivalClock(),
	survivalTimeText(Text(game.getFont(), "", 25))
{
	window.setMouseCursorVisible(false);
	
	initSurvivalTimeText();

	spawnBall(30.f, { 200.f, 200.f }, { 150.f, 100.f });
	spawnBall(50.f, { 500.f, 300.f }, { -120.f, 160.f });

	survivalClock.restart();
}

void GamePlayScreen::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		player.rotate(90.f);
	}
}

void GamePlayScreen::update(float deltaTime)
{
	float survivalTime = survivalClock.getElapsedTime().asSeconds();
	survivalTimeText.setString("Survival Time: " +
		to_string(survivalTime) + "s");

	player.update(window);
	
	for (auto& ball : balls)
	{
		ball.update(deltaTime, window);

		if (ball.isCollidingWithPlayer(player))
		{
			game.switchToGameOverScreen(survivalTime);
		}
	}
}

void GamePlayScreen::render(RenderWindow& window)
{
	player.draw(window);
	
	for (const auto& ball : balls)
	{
		ball.draw(window);
	}

	window.draw(survivalTimeText);
}

void GamePlayScreen::initSurvivalTimeText()
{
	survivalTimeText.setFillColor(Color::White);

	FloatRect survivalTimeTextBounds = survivalTimeText.getLocalBounds();
	survivalTimeText.setOrigin(survivalTimeTextBounds.size / 2.f);
	survivalTimeText.setPosition(Vector2f(0, 0));
}

void GamePlayScreen::spawnBall(float radius, Vector2f position,
	Vector2f velocity)
{
	Ball ball(radius, position, velocity);
	balls.push_back(ball);
}