#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
	public:
		Bullet(const sf::Vector2f& startPosition, 
			const sf::Vector2f& direction, 
			float speed, 
			float lifespan);

		void update(float deltaTime);
		void draw(sf::RenderWindow& window) const;

		bool isExpired() const;

	private:
		sf::CircleShape bullet;

		sf::Vector2f velocity;
		sf::Vector2f position;
		float lifespan;
		float age;
};

#endif // !BULLET_h

