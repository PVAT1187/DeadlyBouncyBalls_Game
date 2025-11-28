#include "Entities/Ball.h"
#include "Math/MathUtils.h"
#include "Math/PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

constexpr float BLINKING_SPEED = 10.f;

Ball::Ball(float radius, Vector2f position, Vector2f velocity) :
	isFlashing(false), flashTimer(0.f)
{
	ball.setRadius(radius);
	ball.setFillColor(randomColor());
	ball.setOrigin(Vector2f(radius, radius));
	ball.setPosition(position);

	this->position = position;
	this->velocity = velocity;
	mass = radius * radius * radius;
	color = ball.getFillColor();
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

	if (isFlashing)
	{
		flashTimer -= deltaTime;
		
		bool whiteState = static_cast<int>(flashTimer * BLINKING_SPEED) % 2 == 0;

		ball.setFillColor(whiteState ? Color::White : color);

		if (flashTimer <= 0.f)
		{
			isFlashing = false;
			ball.setFillColor(color);
		}
	}
}

void Ball::draw(RenderWindow& window) const
{
	window.draw(ball);
}

void Ball::startBlink(float duration)
{
	isFlashing = true;
	flashTimer = duration;
}

bool Ball::isCollidingWithPlayer(const Player& player) const
{
	return isCircleCollidingWithRectangle(ball.getPosition(),
		ball.getRadius(), player.getRectangle());
}