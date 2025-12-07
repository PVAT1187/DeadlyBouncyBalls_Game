#ifndef PLAYER_H
#define PLAYER_H

#include "Entities/Entity.h"

#include <SFML/Graphics.hpp>

class Player : public Entity
{
	public:
		Player(const sf::Texture& texture);

		void update(float deltaTime, const sf::Vector2u& windowSize) override;
		void draw(sf::RenderWindow& window) const override;

		void setRotationTarget(const sf::Vector2f& target);

		const sf::Sprite& getSprite() const;
		sf::Sprite& getSprite();

		sf::FloatRect getCollisionBounds() const;

	private:
		sf::Sprite sprite;
		sf::Vector2f rotationTarget;

		void move(float deltaTime);
		void clampToWindow(const sf::Vector2u& windowSize);
		void rotate(float deltaTime, const sf::Vector2f& rotationTarget);
};

#endif // !PLAYER_H