#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <SFML/System/Vector2.hpp>
#include <cstdint>

namespace Config
{
	namespace Player
	{
		constexpr float SCALE = 0.3f;
		constexpr float SPEED = 650.f;

		constexpr float ROTATION_OFFSET = 90.f;
		constexpr float ROTATION_SPEED = 450.f;

		constexpr float SHRINK_FACTOR = 0.25f;
		constexpr float FOLLOW_SMOOTHING = 0.7f;
	}

	namespace Ball
	{
		constexpr int INITIAL_COUNT = 2;

		constexpr float MIN_RADIUS = 10.f;
		constexpr float MAX_RADIUS = 50.f;

		constexpr float	MIN_SPEED = 100.f;
		constexpr float MAX_SPEED = 500.f;

		constexpr float RADIUS_DECREASE = 10.f;

		constexpr float DIRECTION_RANDOMNESS = 0.5f;

		constexpr float INITIAL_SPLIT_TIME = 5.f;
		constexpr float SPLIT_TIME_MULTIPLIER = 5.f;

		constexpr float BLINKING_SPEED = 10.f;
		constexpr float	BLINKING_DURATION = 0.5f;
	}

	namespace Bullet
	{
		constexpr float SCALE = 0.05f;
		constexpr float SPEED = 1500.f;
		constexpr float LIFESPAN = 1.f;
		constexpr float SHRINK_FACTOR = 0.2f;
	}

	namespace Aiming
	{
		constexpr float SCALE = 1.f;

		constexpr float DISTANCE_FROM_PLAYER_TIP = 20.f;
		constexpr float DISTANCE_TO_CROSSHAIR = 20.f;

		constexpr int CROSSHAIR_ROW = 6;

		constexpr sf::Vector2i FRAME_SIZE = { 64, 64 };
		constexpr int FRAME_COUNT = 4;

		constexpr float FRAME_DURATION = 0.015f;
	}
	
	namespace Shooting
	{
		constexpr float FIRE_COOLDOWN = 0.2f;
	}

	namespace UI
	{
		constexpr unsigned TITLE_TEXT_SIZE = 100;
		constexpr unsigned BODY_TEXT_SIZE = 25;

		constexpr float TITLE_BODY_SPACING = 100.f;
		constexpr float TITLE_INSTRUCTION_SPACING = 5.f;

		constexpr float BODY_TEXT_SPACING = 50.f;

		constexpr float TITLE_BUTTON_SPACING = 200.f;
		constexpr float BUTTON_SPACING = 80.f;

		constexpr uint8_t DIM_ALPHA = 150;
	}
	
	namespace Button
	{
		constexpr float NORMAL_SCALE = 1.f;
		constexpr float HOVER_SCALE = 1.2f;

		constexpr float SMOOTH_SCALING_MULTIPLIER = 0.2f;

		constexpr unsigned BUTTON_SIZE = 50;

	}
	
	namespace Math
	{
		constexpr float PI = 3.14159265f;
		
		constexpr float RADIAN_TO_DEGREE = 180.f / PI;
		
		constexpr float FULL_CIRCLE_DEGREE = 360.f;
		constexpr float HALF_CIRCLE_DEGREE = 180.f;

		constexpr float MIN_DIRECTION = -1.f;
		constexpr float MAX_DIRECTION = 1.f;

		constexpr int COLOR_MIN = 1;
		constexpr int COLOR_MAX = 255;

		constexpr uint8_t FULL_OPACITY = 255;
	}
	
	namespace Physics
	{
		constexpr float COLLISION_SEPARATION_RATIO = 0.5f;
	}
}

#endif // !GAME_CONFIG_H

