#include "Config/Constants/GameConstants.h"
#include "Core/World/WorldBounds.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;

void PhysicsUtils::clampSpriteToWorldBounds(Vector2f& position,
    const Vector2f& halfSize, const WorldBounds& worldBounds)
{
    position.x = computeClamp(
        position.x, 
        worldBounds.left + halfSize.x, 
        worldBounds.right - halfSize.x);
    position.y = computeClamp(
        position.y, 
        worldBounds.top + halfSize.y, 
        worldBounds.bottom - halfSize.y);
}

void PhysicsUtils::bounceCircleOffWorldBounds(Vector2f& position,
    Vector2f& velocity, float radius, const WorldBounds& worldBounds)
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
    const Vector2f& circlePosition, float circleRadius,
    const FloatRect& spriteBounds)
{
    Vector2f spriteHalfSize(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f);
    Vector2f spriteCenter(
        spriteBounds.position.x + spriteHalfSize.x,
		spriteBounds.position.y + spriteHalfSize.y);

    Vector2f closestPoint;
    closestPoint.x = computeClamp(circlePosition.x,
        spriteCenter.x - spriteHalfSize.x,
        spriteCenter.x + spriteHalfSize.x);
    closestPoint.y = computeClamp(circlePosition.y,
        spriteCenter.y - spriteHalfSize.y,
        spriteCenter.y + spriteHalfSize.y);

    float distanceSquared = computeDistanceSquared(circlePosition, closestPoint);

    return (distanceSquared <= circleRadius * circleRadius);
}

bool PhysicsUtils::isCircleCollidingWithCircle(const Vector2f& positionA,
    float radiusA, const Vector2f& positionB, float radiusB)
{
    float distanceSquared = computeDistanceSquared(positionA, positionB);
    float radiusSum = radiusA + radiusB;

    return (distanceSquared <= radiusSum * radiusSum);
}

void PhysicsUtils::resolveStaticCircleCollision(
    Vector2f& positionA, float radiusA, 
    Vector2f& positionB, float radiusB)
{
    float distance = computeDistance(positionA, positionB);

    if (distance == 0.f)
        distance = 0.01f;

    Vector2f normal = computeNormal(positionA, positionB);

    float overlap = COLLISION_SEPARATION_RATIO * 
        (distance - radiusA - radiusB);

    positionA -= overlap * normal;
    positionB += overlap * normal;
}

void PhysicsUtils::resolveDynamicCircleCollision(Vector2f& velocityA, 
    float massA, Vector2f& velocityB, float massB,
    const Vector2f& normal)
{
    Vector2f tangent(-normal.y, normal.x);

    float dpTanA = computeDotProduct(velocityA, tangent);
    float dpTanB = computeDotProduct(velocityB, tangent);

    float dpNorA = computeDotProduct(velocityA, normal);
    float dpNorB = computeDotProduct(velocityB, normal);

    float momentumA = (dpNorA * (massA - massB) + 2.f * massB * dpNorB) / (massA + massB);
    float momentumB = (dpNorB * (massB - massA) + 2.f * massA * dpNorA) / (massA + massB);

    velocityA = computeVector(tangent, dpTanA, normal, momentumA);
    velocityB = computeVector(tangent, dpTanB, normal, momentumB);
}

void PhysicsUtils::resolveCircleCollisions(Vector2f& positionA,
    Vector2f& velocityA, float radiusA, float massA,
    Vector2f& positionB, Vector2f& velocityB, float radiusB, float massB)
{
    resolveStaticCircleCollision(positionA, radiusA, positionB, radiusB);

    Vector2f normal = computeNormal(positionA, positionB);
    resolveDynamicCircleCollision(velocityA, massA, velocityB, massB, normal);
}