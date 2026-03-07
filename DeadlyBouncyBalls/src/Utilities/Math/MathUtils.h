#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <SFML/System/Vector2.hpp>

namespace MathUtils
{
	float computeClamp(float value, float min, float max);
	float computeMass(float radius);
	sf::Vector2f computeDifference(const sf::Vector2f& positionA, 
		const sf::Vector2f& positionB);

	float computeDotProduct(const sf::Vector2f& vectorA, 
		const sf::Vector2f& vectorB);
	float computeLength(const sf::Vector2f& vector);

	float computeDistanceSquared(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);
	float computeDistance(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);

	sf::Vector2f computeNormal(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);
	sf::Vector2f computeVector(const sf::Vector2f& tangent, float dpTangent, 
		const sf::Vector2f& normal, float dpNormal);

	sf::Vector2f normalize(const sf::Vector2f& vector);
};

#endif // !MATH_UTILS_H
