#include "Core/Systems/Combat/CombatSystem.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"


CombatSystem::CombatSystem() :
	playerHit(false) {}

void CombatSystem::update(Player& player,
	BallManager& ballManager)
{
	auto& bullets = player.getBullets();
	auto& balls = ballManager.getBalls();

	playerHit = collisionDetector.detectPlayerBallCollisions(player, balls);
	
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

bool CombatSystem::isPlayerHit() const
{
	return playerHit;
}