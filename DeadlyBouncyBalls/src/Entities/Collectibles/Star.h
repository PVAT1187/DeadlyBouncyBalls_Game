#ifndef STAR_H
#define STAR_H

#include "Utilities/Animation/AnimatedSprite.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class GameAssets;
class Renderer;
class WorldBounds;

class Star
{
	public:
		Star(const GameAssets& assets, 
			const WorldBounds& worldBounds);

		void update(float deltaTime);
		void draw(Renderer& renderer) const;

		sf::Vector2f getPosition() const;
		int getPoints() const;

		sf::FloatRect getCollisionBounds() const;

		bool isExpired() const;

	private:
		 AnimatedSprite star;

		 sf::Vector2f position;
		 sf::Vector2f collisionBoxSize;

		 float lifetime;
		 int points;
};

#endif // !STAR_H

