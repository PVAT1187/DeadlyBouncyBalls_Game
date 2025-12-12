#include "Core/GameConstants.h"
#include "Utilities/PhysicsUtils.h"
#include "Utilities/MathUtils.h"

#include <iostream>

using namespace sf;
using namespace MathUtils;

void PhysicsUtils::clampSpriteToWindow(Vector2f& position,
    const Vector2f& size, const Vector2u& windowSize)
{
    position.x = computeClamp(position.x, 
        size.x, windowSize.x - size.x);
    position.y = computeClamp(position.y, 
        size.y, windowSize.y - size.y);
}

void PhysicsUtils::bounceCircleOffWindow(Vector2f& position,
    Vector2f& velocity, float radius, const Vector2u& windowSize)
{
    const float windowWidth = static_cast<float>(windowSize.x);
    const float windowHeight = static_cast<float>(windowSize.y);

    float circleLeftEdge = position.x - radius;
    float circleRightEdge = position.x + radius;
    float circleTopEdge = position.y - radius;
    float circleBottomEdge = position.y + radius;

    if (circleLeftEdge <= 0)
    {
        velocity.x = -velocity.x;
        position.x = radius;
    }
    else if (circleRightEdge >= windowWidth)
    {
        velocity.x = -velocity.x;
        position.x = windowWidth - radius;
    }
    
    if (circleTopEdge <= 0)
    {
        velocity.y = -velocity.y;
        position.y = radius;
    }
    else if (circleBottomEdge >= windowHeight)
    {
        velocity.y = -velocity.y;
        position.y = windowHeight - radius;
    }
}

bool PhysicsUtils::isCircleCollidingWithSprite(
    const Vector2f& circlePosition, float circleRadius,
    const sf::FloatRect& spriteBounds)
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
    const sf::Vector2f& normal)
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
    if (isCircleCollidingWithCircle(positionA, radiusA, positionB, radiusB))
    {
        resolveStaticCircleCollision(positionA, radiusA, positionB, radiusB);

        Vector2f normal = computeNormal(positionA, positionB);
        resolveDynamicCircleCollision(velocityA, massA, velocityB, massB, normal);
    }
}