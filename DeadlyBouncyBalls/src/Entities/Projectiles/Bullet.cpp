#include "Entities/Projectiles/Bullet.h"
#include "Utilities/Math/MathUtils.h"

using namespace sf;
using namespace MathUtils;

Bullet::Bullet(const sf::Vector2f& startPosition,
	const sf::Vector2f& direction, float speed, float lifespan) :
	position(startPosition),
	lifespan(lifespan), 
	age(0.0f)
{
	bullet.setPosition(position);
	bullet.setFillColor(Color::Red);
	bullet.setRadius(5.0f);
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

