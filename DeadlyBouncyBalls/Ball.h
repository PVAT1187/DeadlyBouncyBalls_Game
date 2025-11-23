#ifndef BALL_H
#define BALL_H	

#include "Player.h"

class Ball
{
	public:
		Ball(float radius, sf::Vector2f position, sf::Vector2f velocity);

		float getRadius() const;
		sf::Vector2f& getPosition();
		sf::Vector2f& getVelocity();

		void update(float deltaTime, const sf::RenderWindow& window);
		void draw(sf::RenderWindow& window) const;

		bool isCollidingWithPlayer(const Player& player) const;

	private:
		sf::CircleShape ball;

		sf::Vector2f position;
		sf::Vector2f velocity;
};

#endif // !BALL_H
