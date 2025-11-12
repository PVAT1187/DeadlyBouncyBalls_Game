#ifndef BALL_H
#define BALL_H	

#include "Player.h"

#include <SFML/Graphics.hpp>

const float INITIAL_BALL_RADIUS = 10.f;

class Ball
{
	public:
		Ball(const sf::RenderWindow& window);

		void update(float deltaTime, 
			const sf::RenderWindow& window);
		void draw(sf::RenderWindow& window) const;

		bool isCollidingWithPlayer(
			const Player& player) const;

	private:
		sf::CircleShape ball;
		sf::Vector2f velocity;
};

#endif // !BALLS_H
