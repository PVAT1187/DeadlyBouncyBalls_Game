#include "MathUtils.h"

#include <random>

using namespace sf;
using namespace std;

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
	float x = randomFloat(-1.f, 1.f);
	float y = randomFloat(-1.f, 1.f);
	float length = sqrt(x * x + y * y);

	if (length == 0.f)
		return { 1.f, 0.f };

	return { x / length, y / length };
}