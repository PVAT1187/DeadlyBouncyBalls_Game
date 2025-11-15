#include "Ball.h"
#include "MathUtils.h"

using namespace sf;
using namespace MathUtils;

const float INITIAL_BALL_RADIUS = 20.f;

Ball::Ball(const RenderWindow& window)
{
	ball.setRadius(INITIAL_BALL_RADIUS);
	ball.setFillColor(Color::Blue);
	ball.setOrigin(Vector2f(INITIAL_BALL_RADIUS, 
		INITIAL_BALL_RADIUS));
	ball.setPosition(static_cast<Vector2f>
		(window.getSize()) / 4.f);
	velocity = Vector2f(150.f, 200.f);
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