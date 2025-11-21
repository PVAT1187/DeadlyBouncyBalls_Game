#include "MathUtils.h"

using namespace sf;

float MathUtils::computeDotProduct(const Vector2f& vectorA, 
    const Vector2f& vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

Vector2f MathUtils::computeDifferenceVector(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	return vectorA - vectorB;
}

float MathUtils::computeDistanceSquared(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	Vector2f difference = computeDifferenceVector(vectorA, vectorB);
	return computeDotProduct(difference, difference);
}

float MathUtils::computeDistance(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	return sqrt(computeDistanceSquared(vectorA, vectorB));
}

float MathUtils::clamp(float value, float min, float max)
{
	if (value < min)
	{
		return min;
	}
	if (value > max)
	{
		return max;
	}
	return value;
}

Vector2f MathUtils::computeNormal(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	Vector2f difference = computeDifferenceVector(vectorA, vectorB);
	float distance = computeDistance(vectorA, vectorB);
	return difference / distance;
}

Vector2f MathUtils::computeVector(const Vector2f& tangent, float dpTangent,
    const Vector2f& normal, float dpNormal)
{
	return tangent * dpTangent + normal * dpNormal;
}

