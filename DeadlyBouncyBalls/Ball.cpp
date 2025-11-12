#include "Ball.h"
#include "MathUtils.h"

using namespace sf;
using namespace MathUtils;

Ball::Ball(const RenderWindow& window)
{
	ball.setRadius(INITIAL_BALL_RADIUS);
	ball.setFillColor(Color::Blue);
	ball.setPosition(static_cast<Vector2f>
		(window.getSize()) / 4.f);
	velocity = Vector2f(200.f, 150.f);
}

void Ball::update(float deltaTime, const RenderWindow& window)
{
	Vector2f position = ball.getPosition();
	ball.move(velocity * deltaTime);

	bounceCircleOffWindow(position, velocity, 
		ball.getRadius(), window.getSize());
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