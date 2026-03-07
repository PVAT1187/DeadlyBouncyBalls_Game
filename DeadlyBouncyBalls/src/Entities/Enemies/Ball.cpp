#include "Config/Constants/GameConstants.h"
#include "Core/Rendering/Renderer.h"
#include "Entities/Enemies/Ball.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Random/RandomUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace RandomUtils;

Ball::Ball(float radius, Vector2f position, Vector2f velocity) :
	radius(radius), position(position), velocity(velocity), 
	isFlashing(false), flashingTime(BLINKING_DURATION)
{
	ball.setRadius(radius);
	ball.setFillColor(randomColor());
	ball.setOrigin(Vector2f(radius, radius));
	ball.setPosition(position);

	mass = computeMass(radius);
	color = ball.getFillColor();
}

float Ball::getRadius() const
{
	return radius;
}

float Ball::getMass() const
{
	return mass;
}

const Vector2f& Ball::getVelocity() const
{
	return velocity;
}

Vector2f& Ball::getVelocity() 
{
	return velocity;
}

const Vector2f& Ball::getPosition() const
{
	return position;
}

Vector2f& Ball::getPosition() 
{
	return position;
}

void Ball::update(float deltaTime)
{
	move(deltaTime);
	updateFlashing(deltaTime);
}

void Ball::draw(Renderer& renderer) const 
{
	renderer.draw(ball);
}

void Ball::startBlink()
{
	isFlashing = true;
}

void Ball::move(float deltaTime)
{
	position += velocity * deltaTime;
	ball.setPosition(position);
}

void Ball::updateFlashing(float deltaTime)
{
	if (!isFlashing)
		return;

	flashingTime -= deltaTime;

	int whiteState = static_cast<int>(flashingTime * BLINKING_SPEED);

	ball.setFillColor((whiteState & 1) == 0 ? Color::White : color);

	if (flashingTime <= 0.f)
	{
		isFlashing = false;
		ball.setFillColor(color);
	}
}