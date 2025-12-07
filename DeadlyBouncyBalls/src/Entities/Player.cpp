#include "Entities/Player.h"
#include "Math/MathUtils.h"
#include "Math/PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

constexpr float FULL_CIRCLE_DEGREE = 360.f;
constexpr float HALF_CIRCLE_DEGREE = 180.f;

constexpr float RADIAN_TO_DEGREE = 180.f / 3.14159265f;
constexpr float ROTATION_OFFSET = 90.f;
 
constexpr float PLAYER_SCALE = 0.3f;
constexpr float PLAYER_SPEED = 600.f;
constexpr float SHRINK_FACTOR = 0.25f;
constexpr float FOLLOW_SMOOTHING = 0.7f;
constexpr float ROTATION_SPEED = 350.f;

Player::Player(const Texture& texture) :
    sprite(texture)
{
    sprite.setScale({ PLAYER_SCALE, PLAYER_SCALE });
    FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(Vector2f(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f));
}

void Player::update(float deltaTime, const sf::Vector2u& windowSize)
{
    move(deltaTime);
    rotate(deltaTime, rotationTarget);
	clampToWindow(windowSize);
}

void Player::draw(RenderWindow& window) const
{
    window.draw(sprite);
}

void Player::setRotationTarget(const sf::Vector2f& target)
{
	rotationTarget = target;
}

const Sprite& Player::getSprite() const
{
	return sprite;
}

Sprite& Player::getSprite()
{
    return sprite;
}

FloatRect Player::getCollisionBounds() const
{
    FloatRect spriteBounds = sprite.getGlobalBounds();

    float shrinkBoundX = spriteBounds.size.x * SHRINK_FACTOR;
    float shrinkBoundY = spriteBounds.size.y * SHRINK_FACTOR;

    spriteBounds.position.x += shrinkBoundX;
    spriteBounds.position.y += shrinkBoundY;
    spriteBounds.size.x -= shrinkBoundX * 2.f;
    spriteBounds.size.y -= shrinkBoundY * 2.f;

	return spriteBounds;
}

void Player::move(float deltaTime)
{
    Vector2f movement;

    if (Keyboard::isKeyPressed(Keyboard::Scancode::A))
        movement.x -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Scancode::D))
        movement.x += 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Scancode::W))
        movement.y -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Scancode::S))
        movement.y += 1.f;

    if (movement.x != 0.f || movement.y != 0.f)
    {
        float length = sqrt(movement.x * movement.x +
            movement.y * movement.y);
        movement /= length;
    }

    sprite.move(movement * PLAYER_SPEED * deltaTime);
}

void Player::clampToWindow(const Vector2u& windowSize)
{
	Vector2f spritePostion = sprite.getPosition();
    FloatRect spriteBounds = getCollisionBounds();
	Vector2f spriteHalfSize(
        spriteBounds.size.x / 2.f, 
        spriteBounds.size.y / 2.f);

    clampSpriteToWindow(spritePostion, spriteHalfSize, windowSize);

    sprite.setPosition(spritePostion);
}

void Player::rotate(float deltaTime, const sf::Vector2f& rotationTarget)
{
    Vector2f direction = rotationTarget - sprite.getPosition();

    float currentAngle = sprite.getRotation().asDegrees();
    float targetAngle = atan2(direction.y, direction.x) * 
        RADIAN_TO_DEGREE + ROTATION_OFFSET;

    float angleDifference = targetAngle - currentAngle;
    while (angleDifference > HALF_CIRCLE_DEGREE)
		angleDifference -= FULL_CIRCLE_DEGREE;
    while (angleDifference < -HALF_CIRCLE_DEGREE)
        angleDifference += FULL_CIRCLE_DEGREE;

	float maxStep = ROTATION_SPEED * deltaTime;
	float step = computeClamp(angleDifference, -maxStep, maxStep);

    sprite.setRotation(degrees(currentAngle + step));
}   