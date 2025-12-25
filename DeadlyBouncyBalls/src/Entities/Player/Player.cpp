#include "Config/Constants/GameConstants.h"
#include "Entities/Player/Player.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace sf;
using namespace std;
using namespace MathUtils;
using namespace PhysicsUtils;

Player::Player(const GameAssets& assets, const Vector2u& windowSize) :
    playerSprite(assets.getPlayerTexture()),
    aimingSystem(assets.getAimingIconTexture()),
	shootingSystem(assets.getBulletTexture())
{
    playerSprite.setScale({ PLAYER_SCALE, PLAYER_SCALE });
    playerSprite.setPosition(
        Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

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
    aimingSystem.update(deltaTime, playerPosition, mouseTarget);
    
    if (shoot(deltaTime, playerPosition))
        aimingSystem.resetAnimation();
}

void Player::draw(RenderWindow& window) const
{
    aimingSystem.draw(window);
    window.draw(playerSprite);
	shootingSystem.draw(window);
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

void Player::setMouseTarget(const sf::Vector2f& target)
{
    mouseTarget = target;
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

bool Player::shoot(float deltaTime, const Vector2f& playerPosition)
{
	bool isShooting = false;
    
    if (Mouse::isButtonPressed(Mouse::Button::Left))
    {
        Vector2f direction = computeDirection(mouseTarget, playerPosition);
        shootingSystem.shoot(playerPosition, direction);
		isShooting = true;
    }

    shootingSystem.update(deltaTime);

    return isShooting;
}
