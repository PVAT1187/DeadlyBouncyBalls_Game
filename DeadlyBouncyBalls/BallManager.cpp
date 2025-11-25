#include "BallManager.h"
#include "MathUtils.h"
#include "PhysicsUtils.h"

using namespace std;
using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

const float MIN_RADIUS = 10.f;
const float MAX_RADIUS = 50.f;
const float	MIN_SPEED = 100.f;
const float MAX_SPEED = 200.f;

BallManager::BallManager(const RenderWindow& window) 
	: splittingTimer(0.f)
{
	for (int i = 0; i < 2; ++i)
	{
		float radius = MAX_RADIUS;
		
		Vector2f position(randomFloat(radius, window.getSize().x - radius),
			randomFloat(radius, window.getSize().y - radius));

		float speed = randomFloat(MIN_SPEED, MAX_SPEED);
		Vector2f direction = randomDirection();
		Vector2f velocity = direction * speed;

		Ball ball(radius, position, velocity);
		balls.push_back(ball);
	}
}

void BallManager::update(float deltaTime, const sf::RenderWindow& window)
{
	for (auto& ball : balls)
	{
		ball.update(deltaTime, window);
	}

	resolveBallCollisions();

	splittingTimer += deltaTime;
	if (splittingTimer >= 10.f)
	{
		splitBall();
		splittingTimer = 0.f;
	}
}

void BallManager::draw(sf::RenderWindow& window)
{
	for (const auto& ball : balls)
	{
		ball.draw(window);
	}
}

bool BallManager::isGameOver(const Player& player)
{
	for (auto& ball : balls)
	{
		if (ball.isCollidingWithPlayer(player))
		{
			return true;
		}
	}
	return false;
}

void BallManager::resolveBallCollisions()
{
	size_t size = balls.size();
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			resolveCircleCollisions(
				balls[i].getPosition(),
				balls[i].getVelocity(),
				balls[i].getRadius(),
				balls[i].getMass(),

				balls[j].getPosition(),
				balls[j].getVelocity(),
				balls[j].getRadius(),
				balls[j].getMass());
		}
	}
}

void BallManager::splitBall()
{
	vector<Ball> newBalls;
	newBalls.reserve(balls.size());

	for (const auto& ball : balls)
	{
		float newRadius = ball.getRadius() - 10.f;

		if (newRadius < MIN_RADIUS)
		{
			continue;
		}

		Vector2f position = ball.getPosition();
		
		Vector2f parentDirection = normalize(ball.getVelocity());
		Vector2f newDirection = normalize(parentDirection + randomDirection() * 0.5f);
		
		float newSpeed = randomFloat(MIN_SPEED, MAX_SPEED) * (MAX_RADIUS / newRadius);
		
		Vector2f newVelocity = newDirection * newSpeed;

		Ball ball(newRadius, position, newVelocity);
		newBalls.push_back(ball);
	}

	for (auto& newBall : newBalls)
	{
		balls.push_back(newBall);
	}
}