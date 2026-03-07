#ifndef  BOUNDARY_SYSTEM_H
#define  BOUNDARY_SYSTEM_H

#include "Core/World/WorldBounds.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Player;
class BallManager;

class BoundarySystem
{
	public:
		BoundarySystem(const WorldBounds& worldBounds);
		
		void apply(Player& player) const;
		void apply(BallManager& ballManager) const;

	private:
		WorldBounds worldBounds;
};

#endif // ! BOUNDARY_SYSTEM_H

