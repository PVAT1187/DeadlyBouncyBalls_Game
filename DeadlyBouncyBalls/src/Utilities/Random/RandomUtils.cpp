#include "Config/GameConfig.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Random/RandomUtils.h"

#include <random>

int RandomUtils::randomInt(int min, int max)
{
	static std::mt19937 randomNumberGenerator(std::random_device{}());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomNumberGenerator);
}

float RandomUtils::randomFloat(float min, float max)
{
	static std::mt19937 randomNumberGenerator(std::random_device{}());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(randomNumberGenerator);
}

sf::Vector2f RandomUtils::randomDirection()
{
	float x = 0.f;
	float y = 0.f;

	do
	{
		x = randomFloat(
			Config::Math::MIN_DIRECTION,
			Config::Math::MAX_DIRECTION
		);

		y = randomFloat(
			Config::Math::MIN_DIRECTION,
			Config::Math::MAX_DIRECTION
		);

	} while (x == 0.f && y == 0.f);

	return MathUtils::computeNormalized({ x, y });
}

sf::Color RandomUtils::randomColor()
{
	static std::mt19937 randomNumberGenerator(std::random_device{}());
	std::uniform_int_distribution<int> dist(
		Config::Math::COLOR_MIN,
		Config::Math::COLOR_MAX
	);

	return sf::Color(
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		Config::Math::FULL_OPACITY
	);
}