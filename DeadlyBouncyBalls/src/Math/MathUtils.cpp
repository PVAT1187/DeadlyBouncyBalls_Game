#include "Math/MathUtils.h"

#include <random>

using namespace sf;
using namespace std;

constexpr float MIN_DIRECTION = -1.f;
constexpr float MAX_DIRECTION = 1.f;

constexpr uint8_t COLOR_MAX = 255;
constexpr uint8_t FULL_OPACITY = 255;

float MathUtils::computeClamp(float value, float min, float max)
{
	return clamp(value, min, max);
}

float MathUtils::computeDotProduct(const Vector2f& vectorA, 
    const Vector2f& vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

float MathUtils::computeDistanceSquared(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	Vector2f difference = vectorA - vectorB;
	return computeDotProduct(difference, difference);
}

float MathUtils::computeDistance(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	return sqrt(computeDistanceSquared(vectorA, vectorB));
}

Vector2f MathUtils::computeNormal(const Vector2f& vectorA,
	const Vector2f& vectorB)
{
	Vector2f difference = vectorA - vectorB;
	float distance = computeDistance(vectorA, vectorB);

	if (distance == 0.f)
		return { 0.f, 0.f };

	return difference / distance;
}

Vector2f MathUtils::computeVector(const Vector2f& tangent, float dpTangent,
	const Vector2f& normal, float dpNormal)
{
	return tangent * dpTangent + normal * dpNormal;
}

Vector2f MathUtils::normalize(const Vector2f& vector)
{
	float length = sqrt(computeDotProduct(vector, vector));

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
	return Color(
		static_cast<uint8_t>(rand() % COLOR_MAX + 1),
		static_cast<uint8_t>(rand() % COLOR_MAX + 1),
		static_cast<uint8_t>(rand() % COLOR_MAX + 1),
		FULL_OPACITY);
}