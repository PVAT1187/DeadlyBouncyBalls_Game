#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"

class CombatSystem
{
	public:
		void update(Player& player, BallManager& ballManager);
};

#endif // !COMBAT_SYSTEM_H

