#include "Core/GameConstants.h"
#include "Entities/BallManager.h"
#include "Utilities/MathUtils.h"
#include "Utilities/PhysicsUtils.h"

using namespace std;
using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

BallManager::BallManager(const sf::Vector2u& windowSize) :
	splittingTimer(0.f), blinkTriggered(false),
	currentSplitTime(INITIAL_SPLITTING_TIME)
{
	for (int i = 0; i < INITIAL_NUMBER_OF_BALL; ++i)
	{
		float radius = MAX_RADIUS;
		
		Vector2f position(randomFloat(radius, windowSize.x - radius),
			randomFloat(radius, windowSize.y - radius));

		float speed = randomFloat(MIN_SPEED, MAX_SPEED);
		Vector2f direction = randomDirection();
		Vector2f velocity = direction * speed;

		balls.emplace_back(radius, position, velocity);
	}
}

void BallManager::update(float deltaTime, const sf::Vector2u& windowSize)
{	
	updateBalls(deltaTime, windowSize);
	resolveBallCollisions();

	splittingTimer += deltaTime;
	updateBlinking();
	updateSplitting();
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
			return true;
	}
	return false;
}

void BallManager::updateBalls(float deltaTime, const Vector2u& windowSize)
{
	for (auto& ball : balls)
	{
		ball.update(deltaTime, windowSize);
	}
}

void BallManager::updateBlinking()
{
	float splitTimeMinusBlinkDuration = currentSplitTime - BLINKING_DURATION;

	if (!blinkTriggered && splittingTimer >= splitTimeMinusBlinkDuration)
	{
		for (auto& ball : balls)
			ball.startBlink(BLINKING_DURATION);

		blinkTriggered = true;
	}
}

void BallManager::updateSplitting()
{
	if (splittingTimer >= currentSplitTime)
	{
		splitBall();
		currentSplitTime *= SPLIT_TIME_MULTIPLIER;
		blinkTriggered = false;
	}
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

	for (auto& ball : balls)
	{
		float newRadius = ball.getRadius() - AMOUNT_RADIUS_DECREASED_BY;

		if (newRadius < MIN_RADIUS)
			continue;

		Vector2f position = ball.getPosition();
		
		Vector2f parentDirection = normalize(ball.getVelocity());
		Vector2f newDirection = normalize(parentDirection + randomDirection() 
			* DIRECTION_RANDOMNESS_FACTOR);
		
		float newSpeed = randomFloat(MIN_SPEED, MAX_SPEED) * (MAX_RADIUS / newRadius);
		
		Vector2f newVelocity = newDirection * newSpeed;

		newBalls.emplace_back(newRadius, position, newVelocity);
	}

	for (auto& newBall : newBalls)
	{
		balls.push_back(newBall);
	}
}