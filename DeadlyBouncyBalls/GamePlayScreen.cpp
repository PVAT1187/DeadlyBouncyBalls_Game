#include "GamePlayScreen.h"
#include "Game.h"
#include "MathUtils.h"

#include <iostream>

using namespace sf;
using namespace std;
using namespace MathUtils;

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
	spawnBall(40.f, { 400.f, 300.f }, { -120.f, 160.f });
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

	Vector2f difference = positionB - positionA;
	float distance = sqrt(dotProduct(difference, difference));
	
	Vector2f normal = computeNormal(difference, distance);

	float overlap = 0.5f * (radiusA + radiusB - distance);

	ballA.setPosition(positionA - overlap * normal);
	ballB.setPosition(positionB + overlap * normal);
	
	Vector2f tangent(-normal.y, normal.x);

	float dpTanA = dotProduct(velocityA, tangent);
	float dpTanB = dotProduct(velocityB, tangent);

	float dpNorA = dotProduct(velocityA, normal);
	float dpNorB = dotProduct(velocityB, normal);

	Vector2f newVelocityA = computeVector(tangent, dpTanA,
		normal, dpNorB);
	Vector2f newVelocityB = computeVector(tangent, dpTanB,
		normal, dpNorA);

	ballA.setVelocity(newVelocityA);
	ballB.setVelocity(newVelocityB);
}