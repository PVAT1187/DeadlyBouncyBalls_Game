#include "Core/Systems/CollisionDetection/CollisionDetectionSystem.h"
#include "Core/Systems/Combat/CombatSystem.h"

void CombatSystem::update(Player& player,
	BallManager& ballManager)
{
	auto& bullets = player.getBullets();
	auto& balls = ballManager.getBalls();

	CollisionDetectionSystem collisionDetector;
	auto collisions = collisionDetector.detectBulletBallCollisions(
		bullets, balls);

	auto iterEnd = collisions.rend();
	for (auto iterator = collisions.rbegin(); iterator != iterEnd; ++iterator)
	{
		size_t bulletIndex = iterator->first;
		size_t ballIndex = iterator->second;

		ballManager.splitBallOnHit(ballIndex);
		bullets.erase(bullets.begin() + bulletIndex);
	}
}