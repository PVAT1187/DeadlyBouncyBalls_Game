#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "Core/Systems/Shooting/ShootingSystem.h"
#include "Entities/Enemies/BallManager.h"

class CombatSystem
{
	public:
		void update(ShootingSystem& shootingSystem,
			BallManager& ballManager);
};

#endif // !COMBAT_SYSTEM_H

