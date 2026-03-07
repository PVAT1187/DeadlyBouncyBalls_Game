#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <SFML/System/Vector2.hpp>

class Renderer;

struct InputState
{
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
	bool shoot;
	sf::Vector2f mousePosition;
};

class InputSystem
{
	public:
		InputState collect(Renderer& renderer) const;
};

#endif // !INPUT_STATE_H

