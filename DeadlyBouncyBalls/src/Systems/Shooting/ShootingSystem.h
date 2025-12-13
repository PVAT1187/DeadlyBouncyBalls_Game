#ifndef SHOOTING_SYSTEM_H
#define SHOOTING_SYSTEM_H

#include "Entities/Projectiles/Bullet.h"

class ShootingSystem 
{
	public:
		ShootingSystem();

		void update(float deltaTime);
		void draw(sf::RenderWindow& window) const;

		void shoot(const sf::Vector2f& position, 
			const sf::Vector2f& direction);

	private:
		std::vector<Bullet> bullets;

		float fireCooldown;

		void updateBullets(float deltaTime);
		void removeExpiredBullets();
};

#endif // !SHOOTING_SYSTEM_H

