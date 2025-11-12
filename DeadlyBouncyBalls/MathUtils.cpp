#include "MathUtils.h"

using namespace sf;
using namespace std;

void MathUtils::bounceCircleOffWindow(Vector2f& position, 
    Vector2f& velocity, float radius, const Vector2u& windowSize)
{
    float circleLeftEdge = position.x - radius;
    float circleRightEdge = position.x + radius;
    float circleTopEdge = position.y - radius;
    float circleBottomEdge = position.y + radius;

    if (circleLeftEdge <= 0 ||
        circleRightEdge >= windowSize.x)
    {
        velocity.x = -velocity.x;
    }
    if (circleTopEdge <= 0 ||
        circleBottomEdge >= windowSize.y)
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