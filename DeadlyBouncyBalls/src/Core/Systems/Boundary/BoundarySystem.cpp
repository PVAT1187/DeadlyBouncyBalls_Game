#include "Core/Systems/Boundary/BoundarySystem.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"
#include "Utilities/Physics/PhysicsUtils.h"

void BoundarySystem::apply(
    Player& player,
    const WorldBounds& worldBounds) const
{
    sf::Vector2f spritePosition = player.getPosition();
    sf::FloatRect spriteBounds = player.getCollisionBounds();
    sf::Vector2f spriteHalfSize(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f
    );

    PhysicsUtils::clampSpriteToWorldBounds(
        spritePosition, 
        spriteHalfSize, 
        worldBounds
    );

    player.setPosition(spritePosition);
}

void BoundarySystem::apply(
    BallManager& ballManager,
    const WorldBounds& worldBounds) const
{
	auto& balls = ballManager.getBalls();
    for (auto& ball : balls)
    {
        PhysicsUtils::bounceCircleOffWorldBounds(
            ball.getPosition(),
            ball.getVelocity(),
            ball.getRadius(),
            worldBounds
        );
    }
}
