#include "Config/GameConfig.h"
#include "Core/Input/Input.h"
#include "Core/Systems/Movement/MovementSystem.h"
#include "Entities/Player/Player.h"
#include "Utilities/Math/MathUtils.h"

void MovementSystem::apply(
	Player& player,
	const Input& input,
	float deltaTime)
{
	MovementComponent& movement = player.movement;

	movement.velocity = { 0.f, 0.f };

	if (input.moveLeft)
		movement.velocity.x -= 1.f;
	if (input.moveRight)
		movement.velocity.x += 1.f;
	if (input.moveUp)
		movement.velocity.y -= 1.f;
	if (input.moveDown)
		movement.velocity.y += 1.f;

	if (movement.velocity.x != 0.f || movement.velocity.y != 0.f)
		movement.velocity = MathUtils::computeNormalized(
			movement.velocity
		);

	player.setPosition(player.getPosition() + 
		movement.velocity * Config::Player::SPEED * deltaTime
	);
}