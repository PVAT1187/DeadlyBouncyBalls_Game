#include "Core/Systems/Combat/CombatSystem.h"
#include "Core/Events/GameEvents.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"
#include "Entities/Projectiles/BulletManager.h"
#include "Entities/Collectibles/StarManager.h"

CombatSystem::CombatSystem(EventBus& eventBus) 
	: eventBus(eventBus) {}

void CombatSystem::update(
	Player& player,
	BallManager& ballManager,
	BulletManager& bulletManager,
	StarManager& starManager)
{
	auto& balls = ballManager.getBalls();
	auto& bullets = bulletManager.getBullets();
	auto& stars = starManager.getStars();

	bool playerBallCollision = 
		collisionDetector.detectPlayerBallCollisions(player, balls);

	auto bulletBallcollision =
		collisionDetector.detectBulletBallCollisions(bullets, balls);

	auto ballsCollision = 
		collisionDetector.detectBallCollisions(balls);

	auto playerStarCollisions =
		collisionDetector.detectPlayerStarCollisions(player, stars);

	if (playerBallCollision)
		eventBus.emit(PlayerHit{});
	
	for (const auto& [bulletIndex, ballIndex] : bulletBallcollision)
	{
		eventBus.emit(BulletHit{ bulletIndex });
		eventBus.emit(BallHit{ ballIndex });
	}

	for (const auto& starIndex : playerStarCollisions)
	{
		eventBus.emit(StarCollected{ starIndex });
	}

	ballManager.resolveBallCollisions(ballsCollision);
}