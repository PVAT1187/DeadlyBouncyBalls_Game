#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Ball;

class Bullet
{
	public:
		Bullet(const sf::Texture& bulletTexture,
			const sf::Vector2f& startPosition, 
			const sf::Vector2f& direction, 
			float speed, 
			float lifespan);

		void update(float deltaTime);
		void draw(sf::RenderWindow& window) const;

		sf::FloatRect getCollisionBounds() const;

		bool isExpired() const;

	private:
		sf::Sprite bulletSprite;

		sf::Vector2f velocity;
		sf::Vector2f position;
		float lifespan;
		float age;
};

#endif // !BULLET_h

