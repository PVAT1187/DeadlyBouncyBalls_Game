#include "Systems/Shooting/ShootingSystem.h"

using namespace sf;
using namespace std;

ShootingSystem::ShootingSystem()
{
	fireCooldown = 0.0f;
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

void ShootingSystem::shoot(const sf::Vector2f& position,
	const sf::Vector2f& direction)
{
	if (fireCooldown > 0.f)
		return;

	bullets.emplace_back(position, direction, 1500.f, 2.f);

	fireCooldown = 0.2f;
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