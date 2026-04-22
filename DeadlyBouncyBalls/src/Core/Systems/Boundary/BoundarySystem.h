#ifndef  BOUNDARY_SYSTEM_H
#define  BOUNDARY_SYSTEM_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Player;
class BallManager;
struct WorldBounds;

class BoundarySystem
{
	public:		
		void apply(Player& player,
			const WorldBounds& worldBounds) const;
		void apply(BallManager& ballManager,
			const WorldBounds& worldBounds) const;
};

#endif // ! BOUNDARY_SYSTEM_H

