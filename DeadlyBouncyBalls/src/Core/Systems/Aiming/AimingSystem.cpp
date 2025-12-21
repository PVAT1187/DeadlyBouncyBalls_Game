#include "Config/Constants/GameConstants.h"
#include "Core/Systems/Aiming/AimingSystem.h"
#include "Utilities/Math/MathUtils.h"

using namespace sf;
using namespace MathUtils;

AimingSystem::AimingSystem(const Texture& crosshairTexture) :
	crosshairSprite(crosshairTexture,
		CROSSHAIR_ROW_INDEX,
		CROSSHAIR_FRAME_SIZE,
		CROSSHAIR_FRAME_COUNT,
		CROSSHAIR_FRAME_DURATION),
	aimingLine(PrimitiveType::Lines, 2)
{
	crosshairSprite.setScale({ CROSSHAIR_SCALE, CROSSHAIR_SCALE });
	FloatRect aimingIconBounds = crosshairSprite.getLocalBounds();
	crosshairSprite.setOrigin(Vector2f(
		aimingIconBounds.size.x / 2.f,
		aimingIconBounds.size.y / 2.f));

	aimingLine[0].color = Color::Red;
	aimingLine[1].color = Color::Red;
}

void AimingSystem::update(float deltaTime,
	const Vector2f& playerPosition, 
	const sf::Vector2f& aimingTarget)
{
	aimAtTarget(playerPosition, aimingTarget);
	crosshairSprite.update(deltaTime);
}

void AimingSystem::draw(RenderWindow& window) const
{
	//window.draw(aimingLine);
	crosshairSprite.draw(window);
}

void AimingSystem::resetAnimation()
{
	crosshairSprite.reset();
}

void AimingSystem::aimAtTarget(const Vector2f& playerPosition, 
	const Vector2f& aimingTarget)
{
	Vector2f direction = normalize(
		computeDirection(aimingTarget, playerPosition));

	Vector2f tipPosition = playerPosition + direction
		* DISTANCE_FROM_PLAYER_TIP;
	Vector2f aimingIconPosition = aimingTarget - direction
		* DISTANCE_TO_CROSSHAIR;

	aimingLine[0].position = tipPosition;
	aimingLine[1].position = aimingIconPosition;

	crosshairSprite.setPosition(aimingIconPosition);
}