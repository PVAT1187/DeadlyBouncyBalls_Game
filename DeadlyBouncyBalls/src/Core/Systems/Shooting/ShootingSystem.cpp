#include "Config/Constants/GameConstants.h"
#include "Core/Systems/Shooting/ShootingSystem.h"

using namespace sf;
using namespace std;

ShootingSystem::ShootingSystem(const sf::Texture& bulletTexture) :
	fireCooldown(0.f), bulletTexture(bulletTexture) {
}

void ShootingSystem::update(float deltaTime)
{
	fireCooldown -= deltaTime;
	updateBullets(deltaTime);
	removeExpiredBullets();
}

void ShootingSystem::draw(sf::RenderWindow& window) const
{
	for (const auto& bullet : bullets)
	{
		bullet.draw(window);
	}
}

vector<Bullet>& ShootingSystem::getBullets()
{
	return bullets;
}

void ShootingSystem::shoot(const sf::Vector2f& position,
	const sf::Vector2f& direction)
{
	if (fireCooldown > 0.f)
		return;

	bullets.emplace_back(bulletTexture, position, direction, BULLET_SPEED, BULLET_LIFESPAN);

	fireCooldown = FIRE_COOLDOWN;
}

void ShootingSystem::updateBullets(float deltaTime)
{
	for (auto& bullet : bullets)
	{
		bullet.update(deltaTime);
	}
}

void ShootingSystem::removeExpiredBullets()
{
	bullets.erase(remove_if(bullets.begin(), bullets.end(),
		[](const Bullet& bullet) { return bullet.isExpired(); }),
		bullets.end());
}