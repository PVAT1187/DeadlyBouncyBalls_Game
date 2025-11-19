#include "MathUtils.h"

using namespace sf;
using namespace std;

Vector2f MathUtils::computeNormal(const Vector2f& difference,
    float distance)
{
	return difference / distance;
}

float MathUtils::dotProduct(const Vector2f& vectorA, 
    const Vector2f& vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

Vector2f MathUtils::computeVector(const Vector2f& tangent, float dpTangent,
    const Vector2f& normal, float dpNormal)
{
	return tangent * dpTangent + normal * dpNormal;
}

void MathUtils::bounceCircleOffWindow(Vector2f& position, 
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
    }
    if (circleTopEdge <= 0 ||
        circleBottomEdge >= windowHeight)
    {
        velocity.y = -velocity.y;
    }
}

bool MathUtils::isCircleCollidingWithRectangle(
    const Vector2f& circlePosition, float circleRadius, 
    const RectangleShape& rectangle)
{
	Vector2f worldRectCenter = rectangle.getPosition();
	Vector2f rectangleHalfSize = rectangle.getSize() / 2.f;
    
    Vector2f closetPoint;
    closetPoint.x = clamp(circlePosition.x,
        worldRectCenter.x - rectangleHalfSize.x,
        worldRectCenter.x + rectangleHalfSize.x);
    closetPoint.y = clamp(circlePosition.y,
        worldRectCenter.y - rectangleHalfSize.y,
        worldRectCenter.y + rectangleHalfSize.y);

    Vector2f differenceVector = circlePosition - closetPoint;
    float distanceSquared =
        differenceVector.x * differenceVector.x +
        differenceVector.y * differenceVector.y;

    return (distanceSquared <= circleRadius * circleRadius);
}

bool MathUtils::isCircleCollidingWithCircle(const Vector2f& positionA,
    float radiusA, const Vector2f& positionB, float radiusB)
{
	Vector2f difference = positionA - positionB;
    
    float distanceSquared =
        difference.x * difference.x +
        difference.y * difference.y;
    float radiusSum = radiusA + radiusB;

	return (distanceSquared <= radiusSum * radiusSum);
}