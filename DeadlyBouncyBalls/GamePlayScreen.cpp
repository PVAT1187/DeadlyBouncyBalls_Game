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

	spawnBall(50.f, { 200.f, 200.f }, { 150.f, 100.f });
	spawnBall(50.f, { 400.f, 300.f }, { -120.f, 160.f });
	spawnBall(50.f, { 800.f, 400.f }, { 200.f, -140.f });

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
	}

	size_t size = balls.size();
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			if (balls[i].isCollidingWithBall(balls[j]))
			{
				resolveBallCollisions(balls[i], balls[j]);
			}
		}
	}

	for (auto& ball : balls)
	{
		if (ball.isCollidingWithPlayer(player))
		{
			game.switchToGameOverScreen(survivalTime);
			return;
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

void GamePlayScreen::resolveBallCollisions(Ball& ballA, Ball& ballB)
{
	float radiusA = ballA.getRadius();
	float radiusB = ballB.getRadius();
	
	Vector2f positionA = ballA.getPosition();
	Vector2f positionB = ballB.getPosition();

	Vector2f velocityA = ballA.getVelocity();
	Vector2f velocityB = ballB.getVelocity();

	Vector2f deltaPosition = positionB - positionA;
	float distance = sqrt(deltaPosition.x * deltaPosition.x +
		deltaPosition.y * deltaPosition.y);
	
	Vector2f normal = deltaPosition / distance;

	float overlap = 0.5f * (radiusA + radiusB - distance);

	ballA.setPosition(positionA - overlap * normal);
	ballB.setPosition(positionB + overlap * normal);
	
	Vector2f tangent(-normal.y, normal.x);

	float dpTanA = velocityA.x * tangent.x + velocityA.y * tangent.y;
	float dpTanB = velocityB.x * tangent.x + velocityB.y * tangent.y;

	float dpNorA = velocityA.x * normal.x + velocityA.y * normal.y;
	float dpNorB = velocityB.x * normal.x + velocityB.y * normal.y;

	Vector2f newVelocityA = tangent * dpTanA + normal * dpNorB;
	Vector2f newVelocityB = tangent * dpTanB + normal * dpNorA;

	ballA.setVelocity(newVelocityA);
	ballB.setVelocity(newVelocityB);
}