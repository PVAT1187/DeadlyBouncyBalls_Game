#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "Core/Systems/CollisionDetection/CollisionDetectionSystem.h"
#include "Core/Events/EventBus/EventBus.h"

class Player;
class BallManager;
class BulletManager;

class CombatSystem
{
	public:
		CombatSystem(EventBus& eventBus);
		
		void update(Player& player,
			BallManager& ballManager,
			BulletManager& bulletManager);

	private:
		EventBus& eventBus;
		CollisionDetectionSystem collisionDetector;
};

#endif // !COMBAT_SYSTEM_H

