#include "GameConstants.h"
#include "Entities/Player.h"
#include "Math/MathUtils.h"
#include "Math/PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

Player::Player(const Texture& playerTexture,
    const sf::Texture& aimingIconTexture) :
    playerSprite(playerTexture),
    aimingIconSprite(aimingIconTexture),
    aimingLine(PrimitiveType::Lines, 2)
{
	updatePlayerSprite();
	updateAimingIconSprite();
}

void Player::update(float deltaTime, const sf::Vector2u& windowSize)
{
    move(deltaTime);
    rotate(deltaTime, mouseTarget);
	aimAtTarget(mouseTarget);
	clampToWindow(windowSize);
}

void Player::draw(RenderWindow& window) const
{
    window.draw(playerSprite);
	window.draw(aimingIconSprite);
	window.draw(aimingLine);
}

void Player::setMouseTarget(const sf::Vector2f& target)
{
    mouseTarget = target;
}

const Sprite& Player::getSprite() const
{
	return playerSprite;
}

Sprite& Player::getSprite()
{
    return playerSprite;
}

FloatRect Player::getCollisionBounds() const
{
    FloatRect spriteBounds = playerSprite.getGlobalBounds();

    float shrinkBoundX = spriteBounds.size.x * SHRINK_FACTOR;
    float shrinkBoundY = spriteBounds.size.y * SHRINK_FACTOR;

    spriteBounds.position.x += shrinkBoundX;
    spriteBounds.position.y += shrinkBoundY;
    spriteBounds.size.x -= shrinkBoundX * 2.f;
    spriteBounds.size.y -= shrinkBoundY * 2.f;

	return spriteBounds;
}

void Player::updatePlayerSprite()
{
    playerSprite.setScale({ PLAYER_SCALE, PLAYER_SCALE });
    FloatRect spriteBounds = playerSprite.getLocalBounds();
    playerSprite.setOrigin(Vector2f(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f));
}

void Player::updateAimingIconSprite()
{
    aimingIconSprite.setScale({ AIMING_ICON_SCALE, AIMING_ICON_SCALE });
    FloatRect aimingIconBounds = aimingIconSprite.getLocalBounds();
    aimingIconSprite.setOrigin(Vector2f(
        aimingIconBounds.size.x / 2.f,
        aimingIconBounds.size.y / 2.f));
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
        float length = sqrt(computeDotProduct(movement, movement));
        movement /= length;
    }

    playerSprite.move(movement * PLAYER_SPEED * deltaTime);
}

void Player::clampToWindow(const Vector2u& windowSize)
{
	Vector2f spritePostion = playerSprite.getPosition();
    FloatRect spriteBounds = getCollisionBounds();
	Vector2f spriteHalfSize(
        spriteBounds.size.x / 2.f, 
        spriteBounds.size.y / 2.f);

    clampSpriteToWindow(spritePostion, spriteHalfSize, windowSize);

    playerSprite.setPosition(spritePostion);
}

void Player::rotate(float deltaTime, const sf::Vector2f& rotationTarget)
{
    Vector2f direction = rotationTarget - playerSprite.getPosition();

    float currentAngle = playerSprite.getRotation().asDegrees();
    float targetAngle = atan2(direction.y, direction.x) * 
        RADIAN_TO_DEGREE + ROTATION_OFFSET;

    float angleDifference = targetAngle - currentAngle;
    while (angleDifference > HALF_CIRCLE_DEGREE)
		angleDifference -= FULL_CIRCLE_DEGREE;
    while (angleDifference < -HALF_CIRCLE_DEGREE)
        angleDifference += FULL_CIRCLE_DEGREE;

	float maxStep = ROTATION_SPEED * deltaTime;
	float step = computeClamp(angleDifference, -maxStep, maxStep);

    playerSprite.setRotation(degrees(currentAngle + step));
}   

void Player::aimAtTarget(const Vector2f& aimingTarget)
{
	Vector2f direction = aimingTarget - playerSprite.getPosition();

	float length = sqrt(computeDotProduct(direction, direction));
    if (length != 0.f)
		direction /= length;

	Vector2f tipPosition = playerSprite.getPosition() + direction
        * DISTANCE_FROM_PLAYER_TIP;

	aimingLine[0].position = tipPosition;
	aimingLine[1].position = aimingTarget;

	aimingLine[0].color = Color::Red;
	aimingLine[1].color = Color::Red;

	aimingIconSprite.setPosition(aimingTarget);
}