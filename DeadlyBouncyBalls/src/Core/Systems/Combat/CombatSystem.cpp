#include "Core/Systems/Combat/CombatSystem.h"
#include "Core/Events/GameEvents.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"
#include "Entities/Projectiles/BulletManager.h"

CombatSystem::CombatSystem(EventBus& eventBus) 
	: eventBus(eventBus) {}

void CombatSystem::update(
	Player& player,
	BallManager& ballManager,
	BulletManager& bulletManager)
{
	auto& balls = ballManager.getBalls();
	auto& bullets = bulletManager.getBullets();

	bool playerBallCollision = 
		collisionDetector.detectPlayerBallCollisions(player, balls);

	auto bulletBallcollision =
		collisionDetector.detectBulletBallCollisions(bullets, balls);

	auto ballsCollision = 
		collisionDetector.detectBallCollisions(balls);

	if (playerBallCollision)
	{
		eventBus.emit(PlayerHit{});
	}
	
	for (const auto& [bulletIndex, ballIndex] : bulletBallcollision)
	{
		eventBus.emit(BulletHit{ bulletIndex });
		eventBus.emit(BallHit{ ballIndex });
	}

	ballManager.resolveBallCollisions(ballsCollision);
}