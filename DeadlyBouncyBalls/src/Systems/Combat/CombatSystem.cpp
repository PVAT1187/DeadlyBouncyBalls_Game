#include "Systems/Combat/CombatSystem.h"

void CombatSystem::update(ShootingSystem& shootingSystem,
	BallManager& ballManager)
{
	auto& bullets = shootingSystem.getBullets();
	auto& balls = ballManager.getBalls();

	size_t bulletsSize = bullets.size();
	size_t ballsSize = balls.size();

	bool splitHappened = false;
	size_t i = 0;
	while (i < bulletsSize && !splitHappened)
	{
		size_t j = 0;
		while (j < ballsSize)
		{
			if (bullets[i].hitsEnemy(balls[j]))
			{
				ballManager.splitBallOnHit(j);

				bullets.erase(bullets.begin() + i);
				--i;

				splitHappened = true;
				break;
			}
			++j;
		}
		++i;
	}
}