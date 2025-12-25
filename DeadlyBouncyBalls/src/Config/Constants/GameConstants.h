#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <SFML/Graphics.hpp>

using namespace sf;

// ---------------- Player ----------------
constexpr float PLAYER_SCALE = 0.3f;
constexpr float PLAYER_SPEED = 650.f;

constexpr float PLAYER_ROTATION_OFFSET = 90.f;
constexpr float ROTATION_SPEED = 450.f;

constexpr float PLAYER_SHRINK_FACTOR = 0.25f;
constexpr float FOLLOW_SMOOTHING = 0.7f;

// ---------------- Ball ----------------
constexpr float BLINKING_SPEED = 10.f;
constexpr float	BLINKING_DURATION = 0.5f;

// ---------------- Ball Manager ----------------
constexpr int INITIAL_NUMBER_OF_BALL = 2;

constexpr float BALL_MIN_RADIUS = 10.f;
constexpr float BALL_MAX_RADIUS = 50.f;
constexpr float	BALL_MIN_SPEED = 100.f;
constexpr float BALL_MAX_SPEED = 500.f;

constexpr float AMOUNT_RADIUS_DECREASED_BY = 10.f;
constexpr float DIRECTION_RANDOMNESS_FACTOR = 0.5f;
constexpr float INITIAL_SPLITTING_TIME = 5.f;
constexpr float SPLIT_TIME_MULTIPLIER = 5.f;

// ---------------- Bullet ----------------
constexpr float BULLET_SCALE = 0.05f;

constexpr float BULLET_SHRINK_FACTOR = 0.2f;

// ---------------- Aiming System ----------------
constexpr float CROSSHAIR_SCALE = 1.f;

constexpr float DISTANCE_FROM_PLAYER_TIP = 20.f;
constexpr float DISTANCE_TO_CROSSHAIR = 20.f;

constexpr int CROSSHAIR_ROW_INDEX = 6;
constexpr Vector2i CROSSHAIR_FRAME_SIZE = { 64, 64 };
constexpr int CROSSHAIR_FRAME_COUNT = 4;
constexpr float CROSSHAIR_FRAME_DURATION = 0.015f;

// ---------------- Shooting System ----------------
constexpr float BULLET_SPEED = 1500.f;
constexpr float BULLET_LIFESPAN = 1.f;

constexpr float FIRE_COOLDOWN = 0.2f;

// ---------------- UI ----------------
constexpr unsigned int TITLE_TEXT_SIZE = 100;
constexpr unsigned int BODY_TEXT_SIZE = 25;
constexpr float TITLE_BODY_SPACING = 125.f;

constexpr float TITLE_INSTRUCTION_SPACING = 5.f;
constexpr float INSTRUCTION_SPACING = 50.f;

constexpr float TITLE_BUTTON_SPACING = 200.f;
constexpr float BUTTON_SPACING = 80.f;

constexpr uint8_t DIM_ALPHA = 150;

// ---------------- Text Button ----------------
constexpr float NORMAL_SCALE = 1.f;
constexpr float HOVER_SCALE = 1.2f;

constexpr float SMOOTH_SCALING_MULTIPLIER = 0.2f;

constexpr unsigned int BUTTON_SIZE = 50;

// ---------------- Math Utilities ----------------
constexpr float MIN_DIRECTION = -1.f;
constexpr float MAX_DIRECTION = 1.f;

constexpr int COLOR_MIN = 1;
constexpr int COLOR_MAX = 255;
constexpr uint8_t FULL_OPACITY = 255;

constexpr float RADIAN_TO_DEGREE = 180.f / 3.14159265f;
constexpr float FULL_CIRCLE_DEGREE = 360.f;
constexpr float HALF_CIRCLE_DEGREE = 180.f;

// ---------------- Physics Utilities ----------------
constexpr float COLLISION_SEPARATION_RATIO = 0.5f;

#endif // !GAME_CONSTANTS_H

