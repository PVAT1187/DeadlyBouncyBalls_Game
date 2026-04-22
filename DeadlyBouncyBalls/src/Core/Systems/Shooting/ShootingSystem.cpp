#include "Config/GameConfig.h"
#include "Core/Input/Input.h"
#include "Core/Systems/Shooting/ShootingSystem.h"
#include "Components/ShootingComponent.h"
#include "Entities/Player/Player.h"
#include "Entities/Projectiles/BulletManager.h"

void ShootingSystem::apply(
	Player& player,
	BulletManager& bulletManager,
	const Input& input,
	float deltaTime)
{
	ShootingComponent& shooting = player.shooting;
	shooting.cooldown -= deltaTime;

	if (input.shoot && shooting.cooldown <= 0.f)
	{
		bulletManager.spawn(
			player.getPosition(),
			player.aiming.direction,
			Config::Bullet::SPEED,
			Config::Bullet::LIFESPAN
		);

		shooting.cooldown = shooting.fireRate;
		player.aiming.resetAnimation = true;
	}
}
