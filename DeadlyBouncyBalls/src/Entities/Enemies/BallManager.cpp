#include "Config/Constants/GameConstants.h"
#include "Core/Systems/CollisionDetection/CollisionDetectionSystem.h"
#include "Entities/Enemies/BallManager.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

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
		float radius = BALL_MAX_RADIUS;
		
		Vector2f position(randomFloat(radius, windowSize.x - radius),
			randomFloat(radius, windowSize.y - radius));

		float speed = randomFloat(BALL_MIN_SPEED, BALL_MAX_SPEED);
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

void BallManager::draw(sf::RenderWindow& window) const
{
	for (const auto& ball : balls)
	{
		ball.draw(window);
	}
}

const vector<Ball>& BallManager::getBalls() const
{
	return balls;
}

vector<Ball>& BallManager::getBalls()
{
	return balls;
}

void BallManager::splitBallOnHit(size_t index)
{
	Ball& hitBall = balls[index];

	float newRadius = hitBall.getRadius() - BALL_RADIUS_DECREASE_AMOUNT;
	if (newRadius <= BALL_MIN_RADIUS)
	{
		balls.erase(balls.begin() + index);
		return;
	}

	vector<Ball> newBalls;
	newBalls.reserve(balls.size());

	Vector2f position = hitBall.getPosition();

	Vector2f parentDirection = normalize(hitBall.getVelocity());

	Vector2f childDirection1 = normalize(parentDirection + randomDirection()
		* DIRECTION_RANDOMNESS_FACTOR);
	Vector2f childDirection2 = normalize(parentDirection + randomDirection()
		* DIRECTION_RANDOMNESS_FACTOR);

	float newSpeed = randomFloat(BALL_MIN_SPEED, BALL_MAX_SPEED)
		* (BALL_MAX_RADIUS / newRadius);

	Vector2f newVelocity1 = childDirection1 * newSpeed;
	Vector2f newVelocity2 = childDirection2 * newSpeed;

	newBalls.emplace_back(newRadius, position, newVelocity1);
	newBalls.emplace_back(newRadius, position, newVelocity2);

	balls.erase(balls.begin() + index);
	for (const auto& ball : newBalls)
	{
		balls.push_back(ball);
	}
}

bool BallManager::isCollidingWithPlayer(const Player& player) const
{
	CollisionDetectionSystem collisionDetector;
	return collisionDetector.detectPlayerBallCollisions(player, *this);
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
		{
			ball.startBlink();
		}
			
		blinkTriggered = true;
	}
}

void BallManager::updateSplitting()
{
	if (splittingTimer >= currentSplitTime)
	{
		splitBallOnTimer();
		currentSplitTime *= SPLIT_TIME_MULTIPLIER;
		blinkTriggered = false;
	}
}

void BallManager::resolveBallCollisions()
{
	CollisionDetectionSystem collisionDetector;
	auto collisionPairs = collisionDetector.detectBallCollisions(balls);

	for (const auto& pair : collisionPairs)
	{
		size_t i = pair.first;
		size_t j = pair.second;

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

void BallManager::splitBallOnTimer()
{
	vector<Ball> newBalls;
	newBalls.reserve(balls.size());
	
	for (auto& ball : balls)
	{
		float newRadius = ball.getRadius() - BALL_RADIUS_DECREASE_AMOUNT;

		if (newRadius < BALL_MIN_RADIUS)
			continue;

		Vector2f position = ball.getPosition();

		Vector2f parentDirection = normalize(ball.getVelocity());
		Vector2f newDirection = normalize(parentDirection + randomDirection()
			* DIRECTION_RANDOMNESS_FACTOR);

		float newSpeed = randomFloat(BALL_MIN_SPEED, BALL_MAX_SPEED)
			* (BALL_MAX_RADIUS / newRadius);

		Vector2f newVelocity = newDirection * newSpeed;

		newBalls.emplace_back(newRadius, position, newVelocity);
	}

	for (const auto& ball : newBalls)
	{
		balls.push_back(ball);
	}
}