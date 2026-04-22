#include "Utilities/Math/MathUtils.h"

#include <cmath>
#include <algorithm>

float MathUtils::computeClamp(float value, float min, float max)
{
	return std::clamp(value, min, max);
}

float MathUtils::computeMass(float radius)
{
	return radius * radius * radius;
}

float MathUtils::computeDotProduct(
	const sf::Vector2f& vectorA,
    const sf::Vector2f& vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

float MathUtils::computeLength(const sf::Vector2f& vector)
{
	return hypot(vector.x, vector.y);
}

float MathUtils::computeDistanceSquared(
	const sf::Vector2f& vectorA,
	const sf::Vector2f& vectorB)
{
	float dx = vectorA.x - vectorB.x;
	float dy = vectorA.y - vectorB.y;
	return dx * dx + dy * dy;
}

sf::Vector2f MathUtils::computeNormalized(const sf::Vector2f& vector)
{
	float length = computeLength(vector);

	if (length == 0.f)
		return { 0.f, 0.f };

	return vector / length;
}

sf::Vector2f MathUtils::computeVector(
	const sf::Vector2f& tangent, 
	float dpTangent,
	const sf::Vector2f& normal, 
	float dpNormal)
{
	return tangent * dpTangent + normal * dpNormal;
}