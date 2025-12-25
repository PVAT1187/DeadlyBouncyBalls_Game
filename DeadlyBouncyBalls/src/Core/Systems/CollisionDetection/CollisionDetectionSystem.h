#ifndef  COLLISION_DETECTION_SYSTEM_H
#define  COLLISION_DETECTION_SYSTEM_H

#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"
#include "Entities/Projectiles/Bullet.h"

#include <vector>

class CollisionDetectionSystem
{
	public:
		CollisionDetectionSystem() = default;
		
		bool detectPlayerBallCollisions(const Player& player,
			const BallManager& ballManager);

		std::vector<std::pair<size_t, size_t>> detectBulletBallCollisions(
			const std::vector<Bullet>& bullets,
			const std::vector<Ball>& balls) const;

		std::vector<std::pair<size_t, size_t>> detectBallCollisions(
			const std::vector<Ball>& balls) const;
};

#endif // !COLLISION_DETECTION_SYSTEM_H
