#ifndef BALL_H
#define BALL_H	

#include "Entities/Player.h"

class Ball
{
	public:
		Ball(float radius, sf::Vector2f position, sf::Vector2f velocity);

		float getRadius() const;
		float getMass() const;

		const sf::Vector2f getPosition() const;
		sf::Vector2f& getPosition();

		const sf::Vector2f getVelocity() const;
		sf::Vector2f& getVelocity();

		void update(float deltaTime, const sf::Vector2u& windowSize);
		void draw(sf::RenderWindow& window) const;

		void startBlink(float duration);

		bool isCollidingWithPlayer(const Player& player) const;

	private:
		sf::CircleShape ball;

		float mass;
		sf::Vector2f position;
		sf::Vector2f velocity;

		bool isFlashing;
		float flashTimer;
		sf::Color color;
};

#endif // !BALL_H
