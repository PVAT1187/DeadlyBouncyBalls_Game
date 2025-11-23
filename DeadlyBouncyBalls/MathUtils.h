#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "SFML/Graphics.hpp"

namespace MathUtils
{
	float computeDotProduct(const sf::Vector2f& vectorA, 
		const sf::Vector2f& vectorB);

	sf::Vector2f computeDifference(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);
	float computeDistanceSquared(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);
	float computeDistance(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);

	float clamp(float value, float min, float max);

	sf::Vector2f computeNormal(const sf::Vector2f& vectorA,
		const sf::Vector2f& vectorB);
	sf::Vector2f computeVector(const sf::Vector2f& tangent, float dpTangent, 
		const sf::Vector2f& normal, float dpNormal);
};

#endif // !MATH_UTILS_H
