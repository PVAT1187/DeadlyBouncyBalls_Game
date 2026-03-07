#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Bullet
{
	public:
		Bullet(const sf::Texture& bulletTexture,
			const sf::Vector2f& startPosition, 
			const sf::Vector2f& direction, 
			float speed, 
			float lifespan);

		void update(float deltaTime);

		const sf::Sprite& getSprite() const;
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

