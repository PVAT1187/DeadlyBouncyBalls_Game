#include "Config/GameConfig.h"
#include "Core/Rendering/Renderer.h"
#include "Entities/Enemies/Ball.h"
#include "Entities/Projectiles/Bullet.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

Bullet::Bullet(
	const sf::Texture& bulletTexture,
	const sf::Vector2f& startPosition,
	const sf::Vector2f& direction,
	float speed, float lifespan) :
	bullet(bulletTexture),
	position(startPosition),
	lifespan(lifespan), 
	age(0.0f)
{
	bullet.setScale({ 
		Config::Bullet::SCALE,
		Config::Bullet::SCALE 
	});

	sf::FloatRect spriteBounds = bullet.getLocalBounds();

	collisionBoxSize = sf::Vector2f(
		spriteBounds.size.x * Config::Bullet::SCALE,
		spriteBounds.size.y * Config::Bullet::SCALE
	);

	bullet.setOrigin(sf::Vector2f(
		spriteBounds.size.x / 2.f,
		spriteBounds.size.y / 2.f
	));

	bullet.setPosition(position);

	velocity = MathUtils::computeNormalized(direction) * speed;

	float rotationAngle = 
		atan2(direction.y, direction.x) * 
		Config::Math::RADIAN_TO_DEGREE;

	bullet.setRotation(sf::degrees(rotationAngle));
}

void Bullet::update(float deltaTime)
{
	position += velocity * deltaTime;
	age += deltaTime;
	bullet.setPosition(position);
}

void Bullet::draw(Renderer& renderer) const 
{
	renderer.draw(bullet);
}

sf::FloatRect Bullet::getCollisionBounds() const
{
	float shrunkWidth =
		collisionBoxSize.x
		* (1.f - Config::Player::SHRINK_FACTOR * 2.f);
	float shrunkHeight =
		collisionBoxSize.y
		* (1.f - Config::Player::SHRINK_FACTOR * 2.f);

	return sf::FloatRect(
		{ position.x - shrunkWidth / 2.f,
		  position.y - shrunkHeight / 2.f },
		{ shrunkWidth, shrunkHeight }
	);
}

bool Bullet::isExpired() const
{
	return age >= lifespan;
}

