#include "Config/Constants/GameConstants.h"
#include "Systems/Aiming/AimingSystem.h"
#include "Utilities/Math/MathUtils.h"

using namespace sf;
using namespace MathUtils;

AimingSystem::AimingSystem(const Texture& aimingIconTexture) :
	aimingIconSprite(aimingIconTexture), 
	aimingLine(PrimitiveType::Lines, 2)
{
	aimingIconSprite.setScale({ AIMING_ICON_SCALE, AIMING_ICON_SCALE });
	FloatRect aimingIconBounds = aimingIconSprite.getLocalBounds();
	aimingIconSprite.setOrigin(Vector2f(
		aimingIconBounds.size.x / 2.f,
		aimingIconBounds.size.y / 2.f));

	aimingLine[0].color = Color::Red;
	aimingLine[1].color = Color::Red;
}

void AimingSystem::update(const Vector2f& playerPosition, 
	const sf::Vector2f& aimingTarget)
{
	aimAtTarget(playerPosition, aimingTarget);
}

void AimingSystem::draw(RenderWindow& window) const
{
	//window.draw(aimingLine);
	window.draw(aimingIconSprite);
}

void AimingSystem::aimAtTarget(const Vector2f& playerPosition, 
	const Vector2f& aimingTarget)
{
	Vector2f direction = normalize(
		computeDirection(aimingTarget, playerPosition));

	Vector2f tipPosition = playerPosition + direction
		* DISTANCE_FROM_PLAYER_TIP;
	Vector2f aimingIconPosition = aimingTarget - direction
		* DISTANCE_TO_AIMING_ICON;

	aimingLine[0].position = tipPosition;
	aimingLine[1].position = aimingIconPosition;

	aimingIconSprite.setPosition(aimingIconPosition);
}