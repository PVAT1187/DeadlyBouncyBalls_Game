#include "Ball.h"
#include "MathUtils.h"
#include "PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

Ball::Ball(float radius, Vector2f position, Vector2f velocity)
{
	ball.setRadius(radius);
	ball.setFillColor(randomColor());
	ball.setOrigin(Vector2f(radius, radius));
	ball.setPosition(position);

	this->position = position;
	this->velocity = velocity;
	mass = radius * radius * radius;
}

float Ball::getRadius() const
{
	return ball.getRadius();
}

float Ball::getMass() const
{
	return mass;
}

Vector2f& Ball::getVelocity() 
{
	return velocity;
}

Vector2f Ball::getVelocity() const
{
	return velocity;
}

Vector2f& Ball::getPosition() 
{
	return position;
}

Vector2f Ball::getPosition() const
{
	return position;
}

void Ball::update(float deltaTime, const RenderWindow& window)
{
	position += velocity * deltaTime;

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