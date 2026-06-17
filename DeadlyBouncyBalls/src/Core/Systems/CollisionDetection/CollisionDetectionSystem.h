#ifndef COLLISION_DETECTION_SYSTEM_H
#define COLLISION_DETECTION_SYSTEM_H

#include <vector>

class Player;
class Ball;
class Bullet;
class Star;

class CollisionDetectionSystem
{
	public:
		bool detectPlayerBallCollisions(const Player& player,
			const std::vector<Ball>& balls);

		std::vector<std::pair<size_t, size_t>> detectBulletBallCollisions(
			const std::vector<Bullet>& bullets,
			const std::vector<Ball>& balls) const;

		std::vector<std::pair<size_t, size_t>> detectBallCollisions(
			const std::vector<Ball>& balls) const;

		std::vector<size_t> detectPlayerStarCollisions(const Player& player,
			const std::vector<Star>& stars) const;
};

#endif // !COLLISION_DETECTION_SYSTEM_H
