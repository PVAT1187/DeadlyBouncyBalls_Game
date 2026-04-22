#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "Entities/Projectiles/Bullet.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class GameAssets;

class BulletManager
{
	public:
		BulletManager(const GameAssets& assets);

		void update(float deltaTime);
		void draw(Renderer& renderer) const;

		void spawn(const sf::Vector2f& position,
			const sf::Vector2f& direction,
			float speed,
			float lifespan);

		void remove(size_t index);

		std::vector<Bullet>& getBullets();

	private:
		std::vector<Bullet> bullets;
		const sf::Texture& bulletTexture;

		void updateBullets(float deltaTime);
		void removeExpiredBullets();
};

#endif // ! BULLET_MANAGER_H

