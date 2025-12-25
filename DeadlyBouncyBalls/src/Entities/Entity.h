#ifndef  ENTITY_H
#define  ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
	public:
		virtual void update(float deltaTime, const sf::Vector2u& windowSize) = 0;
		virtual void draw(sf::RenderWindow& window) const = 0;
		
		virtual ~Entity() = default;
};

#endif // !ENTITY_H

