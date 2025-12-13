#include "Config/Constants/GameConstants.h"
#include "Utilities/Math/MathUtils.h"

#include <random>
#include <algorithm>

using namespace sf;
using namespace std;

float MathUtils::computeClamp(float value, float min, float max)
{
	return clamp(value, min, max);
}

float MathUtils::computeMass(float radius)
{
	return radius * radius * radius;
}

Vector2f MathUtils::computeDirection(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	return vectorA - vectorB;
}

float MathUtils::computeDotProduct(const Vector2f& vectorA, 
    const Vector2f& vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

float MathUtils::computeLength(const sf::Vector2f& vector)
{
	return sqrt(computeDotProduct(vector, vector));
}

float MathUtils::computeDistanceSquared(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	Vector2f direction = computeDirection(vectorA, vectorB);
	return computeDotProduct(direction, direction);
}

float MathUtils::computeDistance(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	return sqrt(computeDistanceSquared(vectorA, vectorB));
}

Vector2f MathUtils::computeNormal(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	Vector2f direction = computeDirection(vectorA, vectorB);
	float distance = computeLength(direction);

	if (distance == 0.f)
		return { 0.f, 0.f };

	return direction / distance;
}

Vector2f MathUtils::computeVector(const Vector2f& tangent, float dpTangent,
	const Vector2f& normal, float dpNormal)
{
	return tangent * dpTangent + normal * dpNormal;
}

Vector2f MathUtils::normalize(const Vector2f& vector)
{
	float length = computeLength(vector);

	if (length == 0.f)
		return { 1.f, 0.f };

	return vector / length;
}

float MathUtils::randomFloat(float min, float max)
{
	static mt19937 randomNumberGenerator(random_device{}());
	uniform_real_distribution<float> dist(min, max);
	return dist(randomNumberGenerator);
}

Vector2f MathUtils::randomDirection()
{
	float x = 0.f;
	float y = 0.f;
		
	do
	{
		x = randomFloat(MIN_DIRECTION, MAX_DIRECTION);
		y = randomFloat(MIN_DIRECTION, MAX_DIRECTION);
	} 
	while (x == 0.f && y == 0.f);

	return normalize({ x, y });
}

Color MathUtils::randomColor()
{
	static mt19937 randomNumberGenerator(random_device{}());
	uniform_int_distribution<int> dist(COLOR_MIN, COLOR_MAX);
	return sf::Color(
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		FULL_OPACITY
	);
}