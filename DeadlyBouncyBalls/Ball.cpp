#include "Ball.h"
#include "MathUtils.h"

using namespace sf;
using namespace MathUtils;

Ball::Ball(float radius, Vector2f position, Vector2f velocity)
{
	ball.setRadius(radius);
	ball.setFillColor(Color::Blue);
	ball.setOrigin(Vector2f(radius, radius));
	ball.setPosition(position);
	this->velocity = velocity;
}

float Ball::getRadius() const
{
	return ball.getRadius();
}

Vector2f Ball::getPosition() const
{
	return ball.getPosition();
}

Vector2f Ball::getVelocity() const
{
	return velocity;
}

void Ball::setVelocity(const Vector2f& newVelocity)
{
	velocity = newVelocity;
}

void Ball::setPosition(const Vector2f& newPosition)
{
	ball.setPosition(newPosition);
}

void Ball::update(float deltaTime, const RenderWindow& window)
{
	Vector2f position = ball.getPosition();
	position += velocity * deltaTime * 3.f;

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
	return MathUtils::isCircleCollidingWithRectangle(ball.getPosition(),
		ball.getRadius(), player.getRectangle());
}

bool Ball::isCollidingWithBall(const Ball& otherBall) const
{
	return MathUtils::isCircleCollidingWithCircle(
		ball.getPosition(), ball.getRadius(),
		otherBall.ball.getPosition(), otherBall.ball.getRadius());
}