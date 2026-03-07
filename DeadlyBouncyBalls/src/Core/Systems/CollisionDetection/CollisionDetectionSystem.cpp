#include "Core/Systems/CollisionDetection/CollisionDetectionSystem.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/Ball.h"
#include "Entities/Projectiles/Bullet.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace std;
using namespace PhysicsUtils;

bool CollisionDetectionSystem::detectPlayerBallCollisions(
	const Player& player,
	const vector<Ball>& balls)
{
	for (const auto& ball : balls)
	{
		if (isCircleCollidingWithSprite(
			ball.getPosition(),
			ball.getRadius(),
			player.getCollisionBounds()))
		{
			return true;
		}
	}

	return false;
}

vector<pair<size_t, size_t>> 
	CollisionDetectionSystem::detectBulletBallCollisions(
		const vector<Bullet>& bullets,
		const vector<Ball>& balls) const
{
	vector<pair<size_t, size_t>> collisionPairs;

	size_t bulletSize = bullets.size();
	size_t ballSize = balls.size();

	for (size_t i = 0; i < bulletSize; ++i)
	{
		for (size_t j = 0; j < ballSize; ++j)
		{
			if (isCircleCollidingWithSprite(
				balls[j].getPosition(), balls[j].getRadius(),
				bullets[i].getCollisionBounds()))
			{
				collisionPairs.emplace_back(i, j);
			}
		}
	}

	return collisionPairs;
}

vector<pair<size_t, size_t>> 
	CollisionDetectionSystem::detectBallCollisions(
		const vector<Ball>& balls) const
{
	vector<pair<size_t, size_t>> collisionPairs;

	size_t ballSize = balls.size();

	for (size_t i = 0; i < ballSize; ++i)
	{
		for (size_t j = i + 1; j < ballSize; ++j)
		{
			if (isCircleCollidingWithCircle(
				balls[i].getPosition(), balls[i].getRadius(),
				balls[j].getPosition(), balls[j].getRadius()))
			{
				collisionPairs.emplace_back(i, j);
			}
		}
	}

	return collisionPairs;
}