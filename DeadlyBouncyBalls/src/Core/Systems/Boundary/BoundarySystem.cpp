#include "Core/Systems/Boundary/BoundarySystem.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace sf;
using namespace PhysicsUtils;

BoundarySystem::BoundarySystem(const WorldBounds& worldBounds) 
    : worldBounds(worldBounds) {}

void BoundarySystem::apply(Player& player) const
{
    Vector2f spritePosition = player.getPosition();
    FloatRect spriteBounds = player.getCollisionBounds();
    Vector2f spriteHalfSize(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f);

    clampSpriteToWorldBounds(spritePosition, spriteHalfSize, worldBounds);

    player.setPosition(spritePosition);
}

void BoundarySystem::apply(BallManager& ballManager) const
{
	auto& balls = ballManager.getBalls();
    for (auto& ball : balls)
    {
        bounceCircleOffWorldBounds(
            ball.getPosition(),
            ball.getVelocity(),
            ball.getRadius(),
            worldBounds);
    }
}
