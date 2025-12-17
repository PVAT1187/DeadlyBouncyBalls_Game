#include "Config/Constants/GameConstants.h"
#include "Entities/Enemies/Ball.h"
#include "Entities/Projectiles/Bullet.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Physics/PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

Bullet::Bullet(const sf::Vector2f& startPosition,
	const sf::Vector2f& direction, float speed, float lifespan) :
	position(startPosition),
	lifespan(lifespan), 
	age(0.0f)
{
	bullet.setPosition(position);
	bullet.setFillColor(Color::Red);
	bullet.setRadius(BULLET_RADIUS);
	bullet.setOrigin(Vector2f(bullet.getRadius(), bullet.getRadius()));
	velocity = normalize(direction) * speed;
}

void Bullet::update(float deltaTime)
{
	position += velocity * deltaTime;
	age += deltaTime;
	bullet.setPosition(position);
}

void Bullet::draw(sf::RenderWindow& window) const
{
	window.draw(bullet);
}

bool Bullet::isExpired() const
{
	return age >= lifespan;
}

bool Bullet::hitsEnemy(const Ball& ball) const
{
	Vector2f bulletPosition = bullet.getPosition();
	Vector2f ballPosition = ball.getPosition();

	float bulletRadius = bullet.getRadius();
	float ballRadius = ball.getRadius();
	
	return isCircleCollidingWithCircle(bulletPosition, bulletRadius,
		ballPosition, ballRadius);
}

