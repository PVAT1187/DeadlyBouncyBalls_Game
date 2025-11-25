#include "BallManager.h"
#include "MathUtils.h"
#include "PhysicsUtils.h"

using namespace std;
using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

const float MIN_RADIUS = 10.f;
const float MAX_RADIUS = 50.f;
const float	MIN_SPEED = 500.f;
const float MAX_SPEED = 1000.f;

const float AMOUNT_RADIUS_DECREASED_BY = 10.f;

const float SPLITTING_TIME = 10.f;

BallManager::BallManager(const RenderWindow& window) 
	: splittingTimer(0.f), split(false)
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
	if (splittingTimer >= SPLITTING_TIME)
	{
		splitBall();
		splittingTimer = 0.f;
	}

	split = false;
}

void BallManager::draw(sf::RenderWindow& window)
{
	for (const auto& ball : balls)
	{
		ball.draw(window);
	}
}

bool BallManager::isSplit() const
{
	return split;
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
	split = true;
	
	vector<Ball> newBalls;
	newBalls.reserve(balls.size());

	for (const auto& ball : balls)
	{
		float newRadius = ball.getRadius() - AMOUNT_RADIUS_DECREASED_BY;

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