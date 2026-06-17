#include "Config/GameConfig.h"
#include "Core/World/WorldBounds.h"
#include "Entities/Enemies/BallManager.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Random/RandomUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

BallManager::BallManager(const WorldBounds& worldBounds) :
	splittingTimer(0.f), 
	blinkTriggered(false),
	currentSplitTime(Config::Ball::INITIAL_SPLIT_TIME)
{
	for (int i = 0; i < Config::Ball::INITIAL_COUNT; ++i)
	{
		float radius = Config::Ball::MAX_RADIUS;

		sf::Vector2f position(
			RandomUtils::randomFloat(
				radius, 
				worldBounds.right - radius
			),
			RandomUtils::randomFloat(
				radius, 
				worldBounds.bottom - radius
			)
		);

		float speed = RandomUtils::randomFloat(
			Config::Ball::MIN_SPEED,
			Config::Ball::MAX_SPEED
		);

		sf::Vector2f direction = RandomUtils::randomDirection();
		sf::Vector2f velocity = direction * speed;

		balls.emplace_back(radius, position, velocity);
	}
}

void BallManager::update(float deltaTime)
{	
	splittingTimer += deltaTime;
	updateBalls(deltaTime);
	updateBlinking();
	updateSplitting();
}

void BallManager::draw(Renderer& renderer) const
{
	for (const auto& ball : balls)
	{
		ball.draw(renderer);
	}
}

std::vector<Ball>& BallManager::getBalls()
{
	return balls;
}

void BallManager::resolveBallCollisions(
	const std::vector<std::pair<size_t, size_t>>&collisionPairs)
{
	for (const auto& [first, second] : collisionPairs)
	{
		PhysicsUtils::resolveCircleCollisions(
			balls[first].getPosition(),
			balls[first].getVelocity(),
			balls[first].getRadius(),
			balls[first].getMass(),

			balls[second].getPosition(),
			balls[second].getVelocity(),
			balls[second].getRadius(),
			balls[second].getMass()
		);
	}
}

int BallManager::splitBallOnHit(size_t index)
{
	Ball& hitBall = balls[index];

	float newRadius = 
		hitBall.getRadius() - Config::Ball::RADIUS_DECREASE;
	if (newRadius <= Config::Ball::MIN_RADIUS)
	{
		int points = hitBall.getPoints();
		balls.erase(balls.begin() + index);
		return points;
	}

	std::vector<Ball> newBalls;
	newBalls.reserve(balls.size());

	sf::Vector2f position = hitBall.getPosition();

	sf::Vector2f parentDirection = 
		MathUtils::computeNormalized(hitBall.getVelocity());

	sf::Vector2f childDirection1 = 
		MathUtils::computeNormalized(
			parentDirection + RandomUtils::randomDirection()
		* Config::Ball::DIRECTION_RANDOMNESS);
	sf::Vector2f childDirection2 = 
		MathUtils::computeNormalized(
			parentDirection + RandomUtils::randomDirection()
		* Config::Ball::DIRECTION_RANDOMNESS);

	float newSpeed = RandomUtils::randomFloat(
		Config::Ball::MIN_SPEED,
		Config::Ball::MAX_SPEED
	) * (Config::Ball::MAX_RADIUS / newRadius);

	sf::Vector2f newVelocity1 = childDirection1 * newSpeed;
	sf::Vector2f newVelocity2 = childDirection2 * newSpeed;

	newBalls.emplace_back(newRadius, position, newVelocity1);
	newBalls.emplace_back(newRadius, position, newVelocity2);

	balls.erase(balls.begin() + index);
	for (const auto& ball : newBalls)
	{
		balls.push_back(ball);
	}

	return -1;
}

void BallManager::updateBalls(float deltaTime)
{
	for (auto& ball : balls)
	{
		ball.update(deltaTime);
	}
}

void BallManager::updateBlinking()
{
	float splitTimeMinusBlinkDuration = 
		currentSplitTime - Config::Ball::BLINKING_DURATION;

	if (!blinkTriggered && splittingTimer >= 
		splitTimeMinusBlinkDuration)
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
		currentSplitTime *= Config::Ball::SPLIT_TIME_MULTIPLIER;
		blinkTriggered = false;
	}
}

void BallManager::splitBallOnTimer()
{
	std::vector<Ball> newBalls;
	newBalls.reserve(balls.size());
	
	for (auto& ball : balls)
	{
		float newRadius = 
			ball.getRadius() - Config::Ball::RADIUS_DECREASE;

		if (newRadius < Config::Ball::MIN_RADIUS)
			continue;

		sf::Vector2f position = ball.getPosition();

		sf::Vector2f parentDirection = 
			MathUtils::computeNormalized(ball.getVelocity());
		sf::Vector2f newDirection = 
			MathUtils::computeNormalized(
				parentDirection + RandomUtils::randomDirection()
			* Config::Ball::DIRECTION_RANDOMNESS);

		float newSpeed = RandomUtils::randomFloat(
			Config::Ball::MIN_SPEED,
			Config::Ball::MAX_SPEED
		) * (Config::Ball::MAX_RADIUS / newRadius);

		sf::Vector2f newVelocity = newDirection * newSpeed;

		newBalls.emplace_back(newRadius, position, newVelocity);
	}

	for (const auto& ball : newBalls)
	{
		balls.push_back(ball);
	}
}