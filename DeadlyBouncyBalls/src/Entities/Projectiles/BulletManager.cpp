#include "Core/Assets/GameAssets.h"
#include "Entities/Projectiles/BulletManager.h"

BulletManager::BulletManager(const GameAssets& assets) 
	: bulletTexture(assets.getTexture(TextureId::BULLET_TEXTURE)) {}

void BulletManager::update(float deltaTime)
{
	updateBullets(deltaTime);
	removeExpiredBullets();
}

void BulletManager::draw(Renderer& renderer) const
{
	for (const auto& bullet : bullets)
	{
		bullet.draw(renderer);
	}
}

void BulletManager::spawn(
	const sf::Vector2f& position,
	const sf::Vector2f& direction,
	float speed,
	float lifespan)
{
	bullets.emplace_back(
		bulletTexture,
		position,
		direction,
		speed,
		lifespan
	);
}

void BulletManager::remove(size_t index)
{
	bullets.erase(bullets.begin() + index);
}

std::vector<Bullet>& BulletManager::getBullets()
{
	return bullets;
}

void BulletManager::updateBullets(float deltaTime)
{
	for (auto& bullet : bullets)
	{
		bullet.update(deltaTime);
	}
}

void BulletManager::removeExpiredBullets()
{
	bullets.erase(remove_if(bullets.begin(), bullets.end(),
		[](const Bullet& bullet) { return bullet.isExpired(); }),
		bullets.end());
}