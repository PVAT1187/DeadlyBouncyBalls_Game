#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include "SFML/Graphics.hpp"

namespace PhysicsUtils
{
	void bounceCircleOffWindow(sf::Vector2f& position, sf::Vector2f& velocity,
		float radius, const sf::Vector2u& windowSize);
	bool isCircleCollidingWithRectangle(const sf::Vector2f& circlePosition,
		float circleRadius, const sf::RectangleShape& rectangle);
	bool isCircleCollidingWithCircle(const sf::Vector2f& positionA,
		float radiusA, const sf::Vector2f& positionB, float radiusB);

	void resolveStaticCircleCollision(sf::Vector2f& positionA,
		float radiusA, sf::Vector2f& positionB, float radiusB);
	void resolveDynamicCircleCollision(sf::Vector2f& velocityA, 
		float massA, sf::Vector2f& velocityB, float massB,
		const sf::Vector2f& normal);
	void resolveCircleCollisions(sf::Vector2f& positionA, 
		sf::Vector2f& velocityA, float radiusA, float massA,
		sf::Vector2f& positionB, sf::Vector2f& velocityB, 
		float radiusB, float massB);
}

#endif // !PHYSICS_UTILS_H
