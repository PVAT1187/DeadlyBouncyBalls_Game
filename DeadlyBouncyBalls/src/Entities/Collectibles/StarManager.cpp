#include "Config/GameConfig.h"
#include "Core/Rendering/Renderer.h"
#include "Core/World/WorldBounds.h"
#include "Entities/Collectibles/StarManager.h"
#include "Utilities/Random/RandomUtils.h"

StarManager::StarManager() : elapsedTime(0.f)
{
	respawnTimer = RandomUtils::randomFloat(
		Config::Star::MIN_SPAWN_TIME,
		Config::Star::MAX_SPAWN_TIME
	);
}

void StarManager::update(
	float deltaTime, 
	const GameAssets& assets, 
	const WorldBounds& bounds)
{
	elapsedTime += deltaTime;
	updateStars(deltaTime);
	spawnStars(deltaTime, assets, bounds);
}

void StarManager::draw(Renderer& renderer) const
{
	for (const auto& star : stars)
	{
		star.draw(renderer);
	}
}

const std::vector<Star>& StarManager::getStars() const 
{
	return stars;
}

int StarManager::collectStar(size_t index)
{
	int points = stars[index].getPoints();
	stars.erase(stars.begin() + index);
	respawnTimer = RandomUtils::randomFloat(
		Config::Star::MIN_SPAWN_TIME,
		Config::Star::MAX_SPAWN_TIME
	);
	return points;
}

void StarManager::updateStars(float deltaTime)
{
	int starsSize = static_cast<int>(stars.size());
	for (int i = starsSize - 1; i >= 0; --i)
	{
		stars[i].update(deltaTime);
		if (stars[i].isExpired())
			stars.erase(stars.begin() + i);
	}
}

void StarManager::spawnStars(
	float deltaTime,
	const GameAssets& assets, 
	const WorldBounds& bounds)
{
	int starCount = getRandomStarCount();
	int starsSize = static_cast<int>(stars.size());

	if (starsSize < starCount)
	{
		respawnTimer -= deltaTime;
		if (respawnTimer <= 0.f)
		{
			int spawnCount = starCount - starsSize;
			for (int i = 0; i < spawnCount; ++i)
			{
				stars.emplace_back(assets, bounds);
			}
			respawnTimer = RandomUtils::randomFloat(
				Config::Star::MIN_SPAWN_TIME,
				Config::Star::MAX_SPAWN_TIME
			);
		}
	}
}

int StarManager::getRandomStarCount() const
{
	if (elapsedTime >= Config::Star::MULTI_SPAWN_TIME)
		return RandomUtils::randomInt(1, 2);
	return 1;
}