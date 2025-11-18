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

bool Ball::isCollidingWithPlayer(
	const Player& player) const
{
	return MathUtils::isCircleCollidingWithRectangle(
		ball.getPosition(), ball.getRadius(), 
		player.getRectangle());
}