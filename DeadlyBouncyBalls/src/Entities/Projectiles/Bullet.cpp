#include "Config/Constants/GameConstants.h"
#include "Entities/Enemies/Ball.h"
#include "Entities/Projectiles/Bullet.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace sf;
using namespace std;
using namespace MathUtils;
using namespace PhysicsUtils;

Bullet::Bullet(const sf::Texture& bulletTexture,
	const sf::Vector2f& startPosition,
	const sf::Vector2f& direction, 
	float speed, float lifespan) :
	bulletSprite(bulletTexture),
	position(startPosition),
	lifespan(lifespan), 
	age(0.0f)
{
	bulletSprite.setScale({ BULLET_SCALE, BULLET_SCALE });
	bulletSprite.setPosition(position);

	FloatRect spriteBounds = bulletSprite.getLocalBounds();
	bulletSprite.setOrigin(Vector2f(
		spriteBounds.size.x / 2.f,
		spriteBounds.size.y / 2.f));

	velocity = normalize(direction) * speed;

	float rotationAngle = atan2(direction.y, direction.x) * RADIAN_TO_DEGREE;
	bulletSprite.setRotation(degrees(rotationAngle));
}

void Bullet::update(float deltaTime)
{
	position += velocity * deltaTime;
	age += deltaTime;
	bulletSprite.setPosition(position);
}

void Bullet::draw(sf::RenderWindow& window) const
{
	window.draw(bulletSprite);
}

FloatRect Bullet::getCollisionBounds() const
{
	FloatRect spriteBounds = bulletSprite.getGlobalBounds();

	float shrinkBoundX = spriteBounds.size.x * BULLET_SHRINK_FACTOR;
	float shrinkBoundY = spriteBounds.size.y * BULLET_SHRINK_FACTOR;

	spriteBounds.position.x += shrinkBoundX;
	spriteBounds.position.y += shrinkBoundY;
	spriteBounds.size.x -= shrinkBoundX * 2.f;
	spriteBounds.size.y -= shrinkBoundY * 2.f;

	return spriteBounds;
}

bool Bullet::isExpired() const
{
	return age >= lifespan;
}

