#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace RandomUtils
{
	float randomFloat(float min, float max);
	sf::Vector2f randomDirection();
	sf::Color randomColor();
}

#endif // !RANDOM_UTILS_H

