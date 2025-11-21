#include "Ball.h"
#include "PhysicsUtils.h"

using namespace sf;
using namespace PhysicsUtils;

Ball::Ball(float radius, Vector2f position, Vector2f velocity)
{
	ball.setRadius(radius);
	ball.setFillColor(Color::Blue);
	ball.setOrigin(Vector2f(radius, radius));
	ball.setPosition(position);
	this->position = position;
	this->velocity = velocity;
}

float Ball::getRadius() const
{
	return ball.getRadius();
}

Vector2f& Ball::getPosition() const
{
	return position;
}

Vector2f& Ball::getVelocity() const
{
	return velocity;
}

void Ball::setVelocity(const Vector2f& newVelocity)
{
	velocity = newVelocity;
}

void Ball::setPosition(const Vector2f& newPosition)
{
	position = newPosition;
	ball.setPosition(newPosition);
}

void Ball::update(float deltaTime, const RenderWindow& window)
{
	Vector2f position = ball.getPosition();
	position += velocity * deltaTime * 5.f;

	bounceCircleOffWindow(position, velocity, 
		ball.getRadius(), window.getSize());

	ball.setPosition(position);
}

void Ball::draw(RenderWindow& window) const
{
	window.draw(ball);
}

bool Ball::isCollidingWithPlayer(const Player& player) const
{
	return isCircleCollidingWithRectangle(ball.getPosition(),
		ball.getRadius(), player.getRectangle());
}