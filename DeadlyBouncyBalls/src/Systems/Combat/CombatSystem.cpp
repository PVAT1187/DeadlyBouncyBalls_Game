#include "Systems/Combat/CombatSystem.h"
#include "Systems/CollisionDetection/CollisionDetectionSystem.h"

void CombatSystem::update(ShootingSystem& shootingSystem,
	BallManager& ballManager)
{
	auto& bullets = shootingSystem.getBullets();
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