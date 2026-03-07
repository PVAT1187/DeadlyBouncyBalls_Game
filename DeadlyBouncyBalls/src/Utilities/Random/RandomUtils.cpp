#include "Config/Constants/GameConstants.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Random/RandomUtils.h"

#include <random>

using namespace sf;
using namespace std;
using namespace MathUtils;

float RandomUtils::randomFloat(float min, float max)
{
	static mt19937 randomNumberGenerator(random_device{}());
	uniform_real_distribution<float> dist(min, max);
	return dist(randomNumberGenerator);
}

Vector2f RandomUtils::randomDirection()
{
	float x = 0.f;
	float y = 0.f;

	do
	{
		x = randomFloat(MIN_DIRECTION, MAX_DIRECTION);
		y = randomFloat(MIN_DIRECTION, MAX_DIRECTION);
	} while (x == 0.f && y == 0.f);

	return normalize({ x, y });
}

Color RandomUtils::randomColor()
{
	static mt19937 randomNumberGenerator(random_device{}());
	uniform_int_distribution<int> dist(COLOR_MIN, COLOR_MAX);
	return sf::Color(
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		static_cast<uint8_t>(dist(randomNumberGenerator)),
		FULL_OPACITY
	);
}