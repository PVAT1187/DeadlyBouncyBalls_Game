#include "Config/Constants/GameConstants.h"
#include "Entities/Player/Player.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

Player::Player(const Texture& playerTexture,
    const sf::Texture& aimingIconTexture,
    const sf::Texture& bulletTexture) :
    playerSprite(playerTexture),
    aimingSystem(aimingIconTexture),
	shootingSystem(bulletTexture)
{
    playerSprite.setScale({ PLAYER_SCALE, PLAYER_SCALE });
    FloatRect spriteBounds = playerSprite.getLocalBounds();
    playerSprite.setOrigin(Vector2f(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f));
}

void Player::update(float deltaTime, const sf::Vector2u& windowSize)
{
    move(deltaTime);
    rotate(deltaTime, mouseTarget);
	clampToWindow(windowSize);

    Vector2f playerPosition = playerSprite.getPosition();
    aimingSystem.update(playerPosition, mouseTarget);
	shoot(deltaTime, playerPosition);
}

void Player::draw(RenderWindow& window) const
{
    aimingSystem.draw(window);
    window.draw(playerSprite);
	shootingSystem.draw(window);
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

    float shrinkBoundX = spriteBounds.size.x * PLAYER_SHRINK_FACTOR;
    float shrinkBoundY = spriteBounds.size.y * PLAYER_SHRINK_FACTOR;

    spriteBounds.position.x += shrinkBoundX;
    spriteBounds.position.y += shrinkBoundY;
    spriteBounds.size.x -= shrinkBoundX * 2.f;
    spriteBounds.size.y -= shrinkBoundY * 2.f;

	return spriteBounds;
}

ShootingSystem& Player::getShootingSystem()
{
	return shootingSystem;
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
		movement = normalize(movement);

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
	Vector2f playerPosition = playerSprite.getPosition();
    Vector2f direction = computeDirection(rotationTarget, playerPosition);

    float currentAngle = playerSprite.getRotation().asDegrees();
    float targetAngle = atan2(direction.y, direction.x) * 
        RADIAN_TO_DEGREE + PLAYER_ROTATION_OFFSET;

    float angleDifference = targetAngle - currentAngle;

    while (angleDifference > HALF_CIRCLE_DEGREE)
		angleDifference -= FULL_CIRCLE_DEGREE;
    while (angleDifference < -HALF_CIRCLE_DEGREE)
        angleDifference += FULL_CIRCLE_DEGREE;

	float maxStep = ROTATION_SPEED * deltaTime;
	float step = computeClamp(angleDifference, -maxStep, maxStep);

    playerSprite.setRotation(degrees(currentAngle + step));
}   

void Player::shoot(float deltaTime, const Vector2f& playerPosition)
{
    if (Mouse::isButtonPressed(Mouse::Button::Left))
    {
        Vector2f direction = computeDirection(mouseTarget, playerPosition);
        shootingSystem.shoot(playerPosition, direction);
    }
    shootingSystem.update(deltaTime);
}
