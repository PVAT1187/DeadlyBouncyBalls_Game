#ifndef SHOOTING_SYSTEM_H
#define SHOOTING_SYSTEM_H

#include "Core/Rendering/Renderer.h"
#include "Entities/Projectiles/Bullet.h"

class ShootingSystem 
{
	public:
		ShootingSystem(const sf::Texture& bulletTexture);

		void update(float deltaTime);
		void draw(Renderer& renderer) const;
		
		std::vector<Bullet>& getBullets();

		void shoot(const sf::Vector2f& position, 
			const sf::Vector2f& direction);

	private:
		std::vector<Bullet> bullets;
		const sf::Texture& bulletTexture;

		float fireCooldown;

		void updateBullets(float deltaTime);
		void removeExpiredBullets();
};

#endif // !SHOOTING_SYSTEM_H

