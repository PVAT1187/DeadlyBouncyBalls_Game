#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <SFML/System/Vector2.hpp>

namespace MathUtils
{
	float computeClamp(float value, float min, float max);
	float computeMass(float radius);

	float computeDotProduct(const sf::Vector2f& vectorA, 
		const sf::Vector2f& vectorB);
	float computeLength(const sf::Vector2f& vector);

	float computeDistanceSquared(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);

	sf::Vector2f computeNormalized(const sf::Vector2f& vector);
	
	sf::Vector2f computeVector(const sf::Vector2f& tangent, 
		float dpTangent, 
		const sf::Vector2f& normal, 
		float dpNormal);
};

#endif // !MATH_UTILS_H
