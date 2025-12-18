#ifndef SHOOTING_SYSTEM_H
#define SHOOTING_SYSTEM_H

#include "Entities/Projectiles/Bullet.h"

class ShootingSystem 
{
	public:
		ShootingSystem(const sf::Texture& bulletTexture);

		void update(float deltaTime);
		void draw(sf::RenderWindow& window) const;
		
		std::vector<Bullet>& getBullets();

		void shoot(const sf::Vector2f& position, 
			const sf::Vector2f& direction);

	private:
		std::vector<Bullet> bullets;
		sf::Texture bulletTexture;

		float fireCooldown;

		void updateBullets(float deltaTime);
		void removeExpiredBullets();
};

#endif // !SHOOTING_SYSTEM_H

