#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include "Core/World/WorldBounds.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace PhysicsUtils
{
	void clampSpriteToWorldBounds(sf::Vector2f& position, 
		const sf::Vector2f& halfSize, 
		const WorldBounds& worldBounds);
	void bounceCircleOffWorldBounds(sf::Vector2f& position, 
		sf::Vector2f& velocity,
		float radius, 
		const WorldBounds& worldBounds);

	bool isCircleCollidingWithSprite(const sf::Vector2f& circlePosition,
		float circleRadius, 
		const sf::FloatRect& spriteBounds);
	bool isCircleCollidingWithCircle(const sf::Vector2f& positionA,
		float radiusA, 
		const sf::Vector2f& positionB, 
		float radiusB);

	sf::Vector2f resolveStaticCircleCollision(sf::Vector2f& positionA,
		float radiusA, 
		sf::Vector2f& positionB, 
		float radiusB);
	void resolveDynamicCircleCollision(sf::Vector2f& velocityA, 
		float massA, 
		sf::Vector2f& velocityB, 
		float massB,
		const sf::Vector2f& normal);
	void resolveCircleCollisions(sf::Vector2f& positionA, 
		sf::Vector2f& velocityA, 
		float radiusA, 
		float massA,
		sf::Vector2f& positionB, 
		sf::Vector2f& velocityB, 
		float radiusB, 
		float massB);
}

#endif // !PHYSICS_UTILS_H
