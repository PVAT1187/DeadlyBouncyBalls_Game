#include "Config/GameConfig.h"
#include "Core/World/WorldBounds.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

void PhysicsUtils::clampSpriteToWorldBounds(
    sf::Vector2f& position,
    const sf::Vector2f& halfSize, 
    const WorldBounds& worldBounds)
{
    position.x = MathUtils::computeClamp(
        position.x, 
        worldBounds.left + halfSize.x, 
        worldBounds.right - halfSize.x
    );

    position.y = MathUtils::computeClamp(
        position.y, 
        worldBounds.top + halfSize.y, 
        worldBounds.bottom - halfSize.y
    );
}

void PhysicsUtils::bounceCircleOffWorldBounds(
    sf::Vector2f& position,
    sf::Vector2f& velocity, 
    float radius, 
    const WorldBounds& worldBounds)
{
    float circleLeftEdge = position.x - radius;
    float circleRightEdge = position.x + radius;
    float circleTopEdge = position.y - radius;
    float circleBottomEdge = position.y + radius;

    if (circleLeftEdge <= worldBounds.left)
    {
        velocity.x *= -1.f;
        position.x = worldBounds.left + radius;
    }
    else if (circleRightEdge >= worldBounds.right)
    {
        velocity.x *= -1.f;
        position.x = worldBounds.right - radius;
    }
    
    if (circleTopEdge <= worldBounds.top)
    {
        velocity.y *= -1.f;
        position.y = worldBounds.top + radius;
    }
    else if (circleBottomEdge >= worldBounds.bottom)
    {
        velocity.y *= -1.f;
        position.y = worldBounds.bottom - radius;
    }
}

bool PhysicsUtils::isCircleCollidingWithSprite(
    const sf::Vector2f& circlePosition, 
    float circleRadius,
    const sf::FloatRect& spriteBounds)
{
    sf::Vector2f spriteHalfSize(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f
    );

    sf::Vector2f spriteCenter(
        spriteBounds.position.x + spriteHalfSize.x,
		spriteBounds.position.y + spriteHalfSize.y
    );

    sf::Vector2f closestPoint;

    closestPoint.x = MathUtils::computeClamp(
        circlePosition.x,
        spriteCenter.x - spriteHalfSize.x,
        spriteCenter.x + spriteHalfSize.x
    );

    closestPoint.y = MathUtils::computeClamp(
        circlePosition.y,
        spriteCenter.y - spriteHalfSize.y,
        spriteCenter.y + spriteHalfSize.y
    );

    float distanceSquared = MathUtils::computeDistanceSquared(
        circlePosition, closestPoint);

    return (distanceSquared <= circleRadius * circleRadius);
}

bool PhysicsUtils::isCircleCollidingWithCircle(
    const sf::Vector2f& positionA,
    float radiusA, 
    const sf::Vector2f& positionB, 
    float radiusB)
{
    float distanceSquared = MathUtils::computeDistanceSquared(
        positionA, positionB);
    float radiusSum = radiusA + radiusB;

    return (distanceSquared <= radiusSum * radiusSum);
}

bool PhysicsUtils::isRectCollidingWithRect(
    const sf::FloatRect& rectangleA,
    const sf::FloatRect& rectangleB)
{
	// return rectangleA.findIntersection(rectangleB).has_value();

    return rectangleA.position.x < rectangleB.position.x + rectangleB.size.x 
        && rectangleB.position.x < rectangleA.position.x + rectangleA.size.x
		&& rectangleA.position.y < rectangleB.position.y + rectangleB.size.y
		&& rectangleB.position.y < rectangleA.position.y + rectangleA.size.y;
}

sf::Vector2f PhysicsUtils::resolveStaticCircleCollision(
    sf::Vector2f& positionA, 
    float radiusA,
    sf::Vector2f& positionB, 
    float radiusB)
{ 
    sf::Vector2f delta = positionA - positionB;
    float distance = MathUtils::computeLength(delta);

    if (distance == 0.f)
        distance = 0.01f;

    if (distance >= radiusA + radiusB)
        return {0.f, 0.f};

    sf::Vector2f normal = delta / distance;

    float overlap = Config::Physics::COLLISION_SEPARATION_RATIO *
        (distance - radiusA - radiusB);

    positionA -= overlap * normal;
    positionB += overlap * normal;

    return normal;
}

void PhysicsUtils::resolveDynamicCircleCollision(
    sf::Vector2f& velocityA,
    float massA, 
    sf::Vector2f& velocityB, 
    float massB,
    const sf::Vector2f& normal)
{
    sf::Vector2f tangent(-normal.y, normal.x);

    float dpTanA = MathUtils::computeDotProduct(velocityA, tangent);
    float dpTanB = MathUtils::computeDotProduct(velocityB, tangent);

    float dpNorA = MathUtils::computeDotProduct(velocityA, normal);
    float dpNorB = MathUtils::computeDotProduct(velocityB, normal);

    float momentumA = (dpNorA * (massA - massB) + 2.f * massB * dpNorB) 
        / (massA + massB);
    float momentumB = (dpNorB * (massB - massA) + 2.f * massA * dpNorA) 
        / (massA + massB);

    velocityA = MathUtils::computeVector(
        tangent, dpTanA, normal, momentumA);
    velocityB = MathUtils::computeVector(
        tangent, dpTanB, normal, momentumB);
}

void PhysicsUtils::resolveCircleCollisions(
    sf::Vector2f& positionA,
    sf::Vector2f& velocityA, 
    float radiusA, 
    float massA,
    sf::Vector2f& positionB, 
    sf::Vector2f& velocityB, 
    float radiusB, 
    float massB)
{
    sf::Vector2f normal = resolveStaticCircleCollision(
        positionA, radiusA, positionB, radiusB);

    if (normal.x == 0.f && normal.y == 0.f)
        return;

    resolveDynamicCircleCollision(
        velocityA, massA, velocityB, massB, normal);
}