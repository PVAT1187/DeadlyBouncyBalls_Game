#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H

#include "Core/World/WorldBounds.h" 
#include "Entities/Enemies/Ball.h"

#include <vector>

class BallManager
{
	public:	
		BallManager(const WorldBounds& worldBounds);

		void update(float deltaTime);
		void draw(Renderer& renderer) const;

		std::vector<Ball>& getBalls();

		void resolveBallCollisions(
			const std::vector<
				std::pair<size_t, size_t>>& collisionPairs);

		bool splitBallOnHit(size_t index);

	private:
		std::vector<Ball> balls;

		float currentSplitTime;
		float splittingTimer;
		bool blinkTriggered;

		void updateBalls(float deltaTime);
		void updateBlinking();
		void updateSplitting();

		void splitBallOnTimer();
};

#endif // !BALL_MANAGER_H

