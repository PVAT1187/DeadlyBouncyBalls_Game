#ifndef BALL_H
#define BALL_H	

#include "Entities/Player/Player.h"

class Ball : public Entity
{
	public:
		Ball(float radius, sf::Vector2f position, sf::Vector2f velocity);

		void update(float deltaTime, const sf::Vector2u& windowSize) override;
		void draw(sf::RenderWindow& window) const override;
		
		float getRadius() const;
		float getMass() const;

		const sf::Vector2f& getPosition() const;
		sf::Vector2f& getPosition();

		const sf::Vector2f& getVelocity() const;
		sf::Vector2f& getVelocity();

		void startBlink(float duration);

		bool isCollidingWithPlayer(const Player& player) const;


	private:
		sf::CircleShape ball;

		float mass;
		float radius;
		sf::Vector2f position;
		sf::Vector2f velocity;

		bool isFlashing;
		float flashingTime;
		sf::Color color;

		void move(float deltaTime, const sf::Vector2u& windowSize);
		void updateFlashing(float deltaTime);
};

#endif // !BALL_H
