#include "Config/GameConfig.h"
#include "Core/Input/Input.h"
#include "Core/Systems/Aiming/AimingSystem.h"
#include "Components/AimingComponent.h"
#include "Entities/Player/Player.h"
#include "Utilities/Math/MathUtils.h"

void AimingSystem::apply(
	Player& player, 
	const Input& input,
	float deltaTime)
{
	AimingComponent& aiming = player.aiming;
	
	if (aiming.resetAnimation)
	{
		aiming.crosshair.reset();
		aiming.resetAnimation = false;
	}

	aiming.target = input.mousePosition;

	sf::Vector2f raw = aiming.target - player.getPosition();
	aiming.direction = MathUtils::computeNormalized(raw);

	float currentAngle = player.getRotation();
	float targetAngle = atan2(
		aiming.direction.y,
		aiming.direction.x
	) * Config::Math::RADIAN_TO_DEGREE 
		+ Config::Player::ROTATION_OFFSET;

	float angleDifference = targetAngle - currentAngle;

	while (angleDifference > Config::Math::HALF_CIRCLE_DEGREE)
		angleDifference -= Config::Math::FULL_CIRCLE_DEGREE;
	while (angleDifference < -Config::Math::HALF_CIRCLE_DEGREE)
		angleDifference += Config::Math::FULL_CIRCLE_DEGREE;

	float maxStep = Config::Player::ROTATION_SPEED * deltaTime;
	float step = MathUtils::computeClamp(
		angleDifference,
		-maxStep,
		maxStep
	);

	player.setRotation(currentAngle + step);

	update(player, deltaTime);
}

void AimingSystem::update(Player& player, float deltaTime)
{
	AimingComponent& aiming = player.aiming;
	
	sf::Vector2f tipPosition = player.getPosition() 
		+ aiming.direction
		* Config::Aiming::DISTANCE_FROM_PLAYER_TIP;
	sf::Vector2f aimingIconPosition = aiming.target 
		- aiming.direction
		* Config::Aiming::DISTANCE_TO_CROSSHAIR;

	aiming.crosshair.setPosition(aimingIconPosition);

	aiming.crosshair.update(deltaTime);
}