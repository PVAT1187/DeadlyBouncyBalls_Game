#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <SFML/Graphics.hpp>

// ---------------- Player ----------------
constexpr float PLAYER_SCALE = 0.3f;
constexpr float PLAYER_SPEED = 650.f;

constexpr float ROTATION_OFFSET = 90.f;
constexpr float ROTATION_SPEED = 450.f;

constexpr float RADIAN_TO_DEGREE = 180.f / 3.14159265f;
constexpr float FULL_CIRCLE_DEGREE = 360.f;
constexpr float HALF_CIRCLE_DEGREE = 180.f;
constexpr float SHRINK_FACTOR = 0.25f;
constexpr float FOLLOW_SMOOTHING = 0.7f;

// ---------------- Aiming System ----------------
constexpr float AIMING_ICON_SCALE = 0.1f;

constexpr float DISTANCE_FROM_PLAYER_TIP = 20.f;
constexpr float DISTANCE_TO_AIMING_ICON = 20.f;

// ---------------- Ball ----------------
constexpr float BLINKING_SPEED = 10.f;

// ---------------- Ball Manager ----------------
constexpr int INITIAL_NUMBER_OF_BALL = 2;

constexpr float MIN_RADIUS = 10.f;
constexpr float MAX_RADIUS = 50.f;
constexpr float	MIN_SPEED = 500.f;
constexpr float MAX_SPEED = 1000.f;

constexpr float AMOUNT_RADIUS_DECREASED_BY = 10.f;
constexpr float DIRECTION_RANDOMNESS_FACTOR = 0.5f;
constexpr float INITIAL_SPLITTING_TIME = 5.f;
constexpr float SPLIT_TIME_MULTIPLIER = 3.f;
constexpr float	BLINKING_DURATION = 0.5f;

// ---------------- Screen ----------------
constexpr unsigned int TITLE_TEXT_SIZE = 100;
constexpr unsigned int BODY_TEXT_SIZE = 25;
constexpr float TEXT_SPACING = 125.f;

// ---------------- Overlay ----------------
constexpr uint8_t DIM_ALPHA = 150;

// ---------------- Text Button ----------------
constexpr float NORMAL_SCALE = 1.f;
constexpr float HOVER_SCALE = 1.2f;

constexpr float SMOOTH_SCALING_MULTIPLIER = 0.2f;

constexpr unsigned int BUTTON_SIZE = 50;
constexpr float TITLE_BUTTON_SPACING = 200.f;
constexpr float BUTTON_SPACING = 80.f;

// ---------------- Math Utilities ----------------
constexpr float MIN_DIRECTION = -1.f;
constexpr float MAX_DIRECTION = 1.f;

constexpr int COLOR_MIN = 1;
constexpr int COLOR_MAX = 255;
constexpr uint8_t FULL_OPACITY = 255;

// ---------------- Physics Utilities ----------------
constexpr float COLLISION_SEPARATION_RATIO = 0.5f;

#endif // !GAME_CONSTANTS_H

