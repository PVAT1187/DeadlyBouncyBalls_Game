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
		void draw(sf::RenderWindow& window) const;

		const std::vector<Ball>& getBalls() const;
		std::vector<Ball>& getBalls();

		void splitBallOnHit(size_t index);
		
		bool isCollidingWithPlayer(const Player& player) const;

	private:
		std::vector<Ball> balls;

		float currentSplitTime;
		float splittingTimer;
		bool blinkTriggered;

		void updateBalls(float deltaTime, const sf::Vector2u& windowSize);
		void updateBlinking();
		void updateSplitting();

		void resolveBallCollisions();
		
		void splitBallOnTimer();
};

#endif // !BALL_MANAGER_H

