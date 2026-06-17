#include "Core/Systems/CollisionDetection/CollisionDetectionSystem.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/Ball.h"
#include "Entities/Projectiles/Bullet.h"
#include "Entities/Collectibles/Star.h"
#include "Utilities/Physics/PhysicsUtils.h"

bool CollisionDetectionSystem::detectPlayerBallCollisions(
	const Player& player,
	const std::vector<Ball>& balls)
{
	for (const auto& ball : balls)
	{
		if (PhysicsUtils::isCircleCollidingWithSprite(
			ball.getPosition(),
			ball.getRadius(),
			player.getCollisionBounds()))
		{
			return true;
		}
	}

	return false;
}

std::vector<std::pair<size_t, size_t>> 
	CollisionDetectionSystem::detectBulletBallCollisions(
		const std::vector<Bullet>& bullets,
		const std::vector<Ball>& balls) const
{
	std::vector<std::pair<size_t, size_t>> collisionPairs;

	size_t bulletsSize = bullets.size();
	size_t ballsSize = balls.size();

	for (size_t i = 0; i < bulletsSize; ++i)
	{
		for (size_t j = 0; j < ballsSize; ++j)
		{
			if (PhysicsUtils::isCircleCollidingWithSprite(
				balls[j].getPosition(), 
				balls[j].getRadius(),
				bullets[i].getCollisionBounds()))
			{
				collisionPairs.emplace_back(i, j);
			}
		}
	}

	// Sort bullet indices in descending order 
	// so CombatSystem removes from the back first 
	// earlier indices stay valid
	std::sort(
		collisionPairs.begin(),
		collisionPairs.end(),
		[](const auto& first, const auto& second)
		{
			return first.second > second.second;
		}
	);

	// Remove duplicate bullet indices, 
	// one bullet can only hit one ball per frame
	collisionPairs.erase(
		std::unique(
			collisionPairs.begin(),
			collisionPairs.end(),
			[](const auto& first, const auto& second)
			{
				return first.second == second.second;
			}
		),
		collisionPairs.end()
	);

	return collisionPairs;
}

std::vector<std::pair<size_t, size_t>> 
	CollisionDetectionSystem::detectBallCollisions(
		const std::vector<Ball>& balls) const
{
	std::vector<std::pair<size_t, size_t>> collisionPairs;

	size_t ballsSize = balls.size();

	for (size_t i = 0; i < ballsSize; ++i)
	{
		for (size_t j = i + 1; j < ballsSize; ++j)
		{
			if (PhysicsUtils::isCircleCollidingWithCircle(
				balls[i].getPosition(), 
				balls[i].getRadius(),
				balls[j].getPosition(),
				balls[j].getRadius()))
			{
				collisionPairs.emplace_back(i, j);
			}
		}
	}

	return collisionPairs;
}

std::vector<size_t> 
	CollisionDetectionSystem::detectPlayerStarCollisions(
		const Player& player,
		const std::vector<Star>& stars) const
{
	std::vector<size_t> collisionPairs;

	for (size_t i = 0; i < stars.size(); ++i)
	{
		if (PhysicsUtils::isRectCollidingWithRect(
			player.getCollisionBounds(),
			stars[i].getCollisionBounds()))
		{
			collisionPairs.push_back(i);
		}
	}

	return collisionPairs;
}