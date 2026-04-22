#ifndef INPUT_H
#define INPUT_H

#include <SFML/System/Vector2.hpp>

struct Input
{
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
	bool shoot;
	sf::Vector2f mousePosition;
};

#endif // !INPUT_H

