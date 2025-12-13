#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H

#include "Entities/Enemies/Ball.h"

#include <SFML/Graphics.hpp>
#include <vector>

class BallManager
{
	public:	
		BallManager(const sf::Vector2u& windowSize);

		void update(float deltaTime, const sf::Vector2u& windowSize);
		void draw(sf::RenderWindow& window);

		bool isGameOver(const Player& player);

	private:
		std::vector<Ball> balls;

		float currentSplitTime;
		float splittingTimer;
		bool blinkTriggered;

		void updateBalls(float deltaTime, const sf::Vector2u& windowSize);
		void updateBlinking();
		void updateSplitting();

		void resolveBallCollisions();
		void splitBall();
};

#endif // !BALL_MANAGER_H

