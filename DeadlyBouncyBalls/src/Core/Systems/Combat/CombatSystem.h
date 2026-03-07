#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "Core/Systems/CollisionDetection/CollisionDetectionSystem.h"

class Player;
class BallManager;

class CombatSystem
{
	public:
		CombatSystem();
		
		void update(Player& player, BallManager& ballManager);

		bool isPlayerHit() const;

	private:
		CollisionDetectionSystem collisionDetector;

		bool playerHit;
};

#endif // !COMBAT_SYSTEM_H

