#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H

#include "SFML/Graphics.hpp"
#include "Ball.h"

#include <vector>

class BallManager
{
	public:	
		BallManager(const sf::RenderWindow& window);

		void update(float deltaTime, const sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);

		bool isSplit() const;
		bool isGameOver(const Player& player);

	private:
		std::vector<Ball> balls;
		float splittingTimer;
		bool split;

		void resolveBallCollisions();
		void splitBall();
};

#endif // !BALL_MANAGER_H

