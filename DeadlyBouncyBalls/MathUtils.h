#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "SFML/Graphics.hpp"

namespace MathUtils
{
	sf::Vector2f computeNormal(const sf::Vector2f& difference, 
		float distance);

	float dotProduct(const sf::Vector2f& vectorA, 
		const sf::Vector2f& vectorB);

	sf::Vector2f computeVector(const sf::Vector2f& tangent, float dpTangent, 
		const sf::Vector2f& normal, float dpNormal);
	
	void bounceCircleOffWindow(sf::Vector2f& position, sf::Vector2f& velocity,
		float radius, const sf::Vector2u& windowSize);

	bool isCircleCollidingWithRectangle(const sf::Vector2f& circlePosition,
		float circleRadius, const sf::RectangleShape& rectangle);

	bool isCircleCollidingWithCircle(const sf::Vector2f& positionA,
		float radiusA, const sf::Vector2f& positionB, float radiusB);
};

#endif // !MATH_UTILS_H
