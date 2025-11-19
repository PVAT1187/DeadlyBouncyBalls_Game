#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "SFML/Graphics.hpp"

namespace MathUtils
{
	void bounceCircleOffWindow(sf::Vector2f& position, sf::Vector2f& velocity,
		float radius, const sf::Vector2u& windowSize);

	bool isCircleCollidingWithRectangle(const sf::Vector2f& circlePosition,
		float circleRadius, const sf::RectangleShape& rectangle);

	bool isCircleCollidingWithCircle(const sf::Vector2f& positionA,
		float radiusA, const sf::Vector2f& positionB, float radiusB);
};

#endif // !MATH_UTILS_H
