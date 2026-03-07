#include "Config/Constants/GameConstants.h"
#include "Core/Assets/GameAssets.h"
#include "Core/World/WorldBounds.h"
#include "Entities/Player/Player.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace sf;
using namespace std;
using namespace MathUtils;
using namespace PhysicsUtils;

Player::Player(const GameAssets& assets,
    const WorldBounds& worldBounds) :
    playerSprite(assets.getPlayerTexture()),
    aimingSystem(assets.getAimingIconTexture()),
	shootingSystem(assets.getBulletTexture())
{
    playerSprite.setPosition(Vector2f(
        worldBounds.right / 2.f,
        worldBounds.bottom / 2.f));
    
    playerSprite.setScale({ PLAYER_SCALE, PLAYER_SCALE });

    FloatRect spriteBounds = playerSprite.getLocalBounds();
    playerSprite.setOrigin(Vector2f(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f));
}

void Player::update(float deltaTime, const InputState& inputState)
{
    move(deltaTime, inputState);
    rotate(deltaTime, inputState);

	Vector2f playerPosition = playerSprite.getPosition();
    aimingSystem.update(deltaTime, playerPosition, 
        inputState.mousePosition);
    
    if (shoot(deltaTime, playerPosition, inputState))
        aimingSystem.resetAnimation();
}

void Player::draw(Renderer& renderer) const
{
    aimingSystem.draw(renderer);
    renderer.draw(playerSprite);
	shootingSystem.draw(renderer);
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

vector<Bullet>& Player::getBullets()
{
    return shootingSystem.getBullets();
}

const Vector2f& Player::getPosition() const
{
	return playerSprite.getPosition();
}

void Player::setPosition(const Vector2f& newPosition)
{
	playerSprite.setPosition(newPosition);
}

void Player::move(float deltaTime, const InputState& inputState)
{
    Vector2f movement;

    if (inputState.moveLeft)
        movement.x -= 1.f;
    if (inputState.moveRight)
        movement.x += 1.f;
    if (inputState.moveUp)
        movement.y -= 1.f;
    if (inputState.moveDown)
        movement.y += 1.f;

    if (movement.x != 0.f || movement.y != 0.f)
		movement = normalize(movement);

    playerSprite.move(movement * PLAYER_SPEED * deltaTime);
}

void Player::rotate(float deltaTime, const InputState& inputState)
{
    Vector2f direction = computeDifference(
        inputState.mousePosition,
        playerSprite.getPosition());

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

bool Player::shoot(float deltaTime, 
    const Vector2f& playerPosition,
    const InputState& inputState)
{
	bool isShooting = false;
    
    if (inputState.shoot)
    {
        Vector2f direction = computeDifference(
            inputState.mousePosition, playerPosition);
        shootingSystem.shoot(playerPosition, direction);
		isShooting = true;
    }

    shootingSystem.update(deltaTime);

    return isShooting;
}
