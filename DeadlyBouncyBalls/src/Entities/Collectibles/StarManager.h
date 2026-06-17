#ifndef STAR_MANAGER_H
#define STAR_MANAGER_H

#include "Entities/Collectibles/Star.h"

#include <vector>

class Renderer;
class GameAssets;
class WorldBounds;

class StarManager
{
	public:
		StarManager();

		void update(float deltaTime, 
			const GameAssets& assets, 
			const WorldBounds& bounds);
		void draw(Renderer& renderer) const;
		
		const std::vector<Star>& getStars() const;

		int collectStar(size_t index);

	private:
		std::vector<Star> stars;

		float respawnTimer;
		float elapsedTime;

		void updateStars(float deltaTime);
		void spawnStars(float deltaTime, 
			const GameAssets& assets,
			const WorldBounds& bounds);
		int getRandomStarCount() const;
};

#endif // !STAR_MANAGER_H

