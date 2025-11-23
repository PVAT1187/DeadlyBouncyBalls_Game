#include "PhysicsUtils.h"
#include "MathUtils.h"

#include <iostream>

using namespace sf;
using namespace MathUtils;

void PhysicsUtils::bounceCircleOffWindow(Vector2f& position,
    Vector2f& velocity, float radius, const Vector2u& windowSize)
{
    const float windowWidth = static_cast<float>(windowSize.x);
    const float windowHeight = static_cast<float>(windowSize.y);

    float circleLeftEdge = position.x - radius;
    float circleRightEdge = position.x + radius;
    float circleTopEdge = position.y - radius;
    float circleBottomEdge = position.y + radius;

    if (circleLeftEdge <= 0 ||
        circleRightEdge >= windowWidth)
    {
        velocity.x = -velocity.x;
        position.x += velocity.x * 0.01f;
    }
    if (circleTopEdge <= 0 ||
        circleBottomEdge >= windowHeight)
    {
        velocity.y = -velocity.y;
        position.y += velocity.y * 0.01f;
    }
}

bool PhysicsUtils::isCircleCollidingWithRectangle(
    const Vector2f& circlePosition, float circleRadius,
    const RectangleShape& rectangle)
{
    Vector2f rectangleCenter = rectangle.getPosition();
    Vector2f rectangleHalfSize = rectangle.getSize() / 2.f;

    Vector2f closestPoint;
    closestPoint.x = clamp(circlePosition.x,
        rectangleCenter.x - rectangleHalfSize.x,
        rectangleCenter.x + rectangleHalfSize.x);
    closestPoint.y = clamp(circlePosition.y,
        rectangleCenter.y - rectangleHalfSize.y,
        rectangleCenter.y + rectangleHalfSize.y);

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
    Vector2f normal = computeNormal(positionA, positionB);

    float overlap = 0.5f * (distance - radiusA - radiusB);

    positionA -= overlap * normal;
    positionB += overlap * normal;
}

void PhysicsUtils::resolveDynamicCircleCollision(Vector2f& velocityA, 
    Vector2f& velocityB, const sf::Vector2f& normal)
{
    Vector2f tangent(-normal.y, normal.x);

    float dpTanA = computeDotProduct(velocityA, tangent);
    float dpTanB = computeDotProduct(velocityB, tangent);

    float dpNorA = computeDotProduct(velocityA, normal);
    float dpNorB = computeDotProduct(velocityB, normal);

    velocityA = computeVector(tangent, dpTanA, normal, dpNorB);
    velocityB = computeVector(tangent, dpTanB, normal, dpNorA);
}

void PhysicsUtils::resolveCircleCollisions(Vector2f& positionA,
    Vector2f& velocityA, float radiusA, Vector2f& positionB,
    Vector2f& velocityB, float radiusB)
{
    if (isCircleCollidingWithCircle(positionA, radiusA, positionB, radiusB))
    {
        resolveStaticCircleCollision(positionA, radiusA, positionB, radiusB);

        Vector2f normal = computeNormal(positionA, positionB);
        resolveDynamicCircleCollision(velocityA, velocityB, normal);
    }
}