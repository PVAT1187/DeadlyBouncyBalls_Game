#include "Entities/Player.h"
#include "Math/MathUtils.h"
#include "Math/PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

constexpr float PLAYER_SCALE = 0.3f;
constexpr float SHRINK_FACTOR = 0.25f;
constexpr float FOLLOW_SMOOTHING = 0.7f;

Player::Player(const Texture& texture) :
    sprite(texture)
{
    sprite.setScale({ PLAYER_SCALE, PLAYER_SCALE });
    FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(Vector2f(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f));
}

void Player::update(const RenderWindow& window)
{
	followMouse(window);
	clampToWindow(window);
}

void Player::draw(RenderWindow& window) const
{
    window.draw(sprite);
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

void Player::clampToWindow(const RenderWindow& window)
{
    const Vector2u& windowSize = window.getSize();

	Vector2f spritePostion = sprite.getPosition();
    FloatRect spriteBounds = getCollisionBounds();
	Vector2f spriteHalfSize(
        spriteBounds.size.x / 2.f, 
        spriteBounds.size.y / 2.f);

    clampSpriteToWindow(spritePostion, spriteHalfSize, windowSize);

    sprite.setPosition(spritePostion);
}

void Player::followMouse(const RenderWindow& window)
{
    Vector2i mousePosition = Mouse::getPosition(window);

    FloatRect spriteBounds = sprite.getGlobalBounds();
    Vector2f spriteCenter(
        spriteBounds.position.x + spriteBounds.size.x / 2.f,
        spriteBounds.position.y + spriteBounds.size.y / 2.f);
    Vector2i worldCenterPixels = window.mapCoordsToPixel(spriteCenter);

    Vector2f difference = static_cast<Vector2f>
        (mousePosition - worldCenterPixels);

    sprite.move(difference * FOLLOW_SMOOTHING);
    Mouse::setPosition(worldCenterPixels, window);
}