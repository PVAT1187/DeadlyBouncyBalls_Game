#ifndef BALL_H
#define BALL_H	

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

class Renderer;

class Ball
{
	public:
		Ball(float radius, sf::Vector2f position, sf::Vector2f velocity);

		void update(float deltaTime);
		void draw(Renderer& renderer) const;

		float getRadius() const;
		float getMass() const;

		const sf::Vector2f& getPosition() const;
		sf::Vector2f& getPosition();

		const sf::Vector2f& getVelocity() const;
		sf::Vector2f& getVelocity();

		void startBlink();

	private:
		sf::CircleShape ball;

		float mass;
		float radius;
		sf::Vector2f position;
		sf::Vector2f velocity;

		bool isFlashing;
		float flashingTime;
		sf::Color color;

		void move(float deltaTime);
		void updateFlashing(float deltaTime);
};

#endif // !BALL_H
