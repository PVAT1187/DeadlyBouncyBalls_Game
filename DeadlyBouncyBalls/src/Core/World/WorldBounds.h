#ifndef WORLD_BOUNDS_H
#define WORLD_BOUNDS_H

#include <SFML/System/Vector2.hpp>

struct WorldBounds
{
	float left;
	float right;
	float top;
	float bottom;

	WorldBounds(const sf::Vector2u& windowSize) 
		: left(0.f),
		right(static_cast<float>(windowSize.x)),
		top(0.f),
		bottom(static_cast<float>(windowSize.y)) {}
};

#endif // !WORLD_BOUNDS_H

