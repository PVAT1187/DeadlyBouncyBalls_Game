#include "Config/GameConfig.h"
#include "Core/Rendering/Renderer.h"
#include "Entities/Enemies/Ball.h"
#include "Utilities/Math/MathUtils.h"
#include "Utilities/Random/RandomUtils.h"

Ball::Ball(
	float radius, 
	sf::Vector2f position, 
	sf::Vector2f velocity) :
	radius(radius), 
	position(position), 
	velocity(velocity), 
	isFlashing(false), 
	flashingTime(Config::Ball::BLINKING_DURATION)
{
	ball.setRadius(radius);
	ball.setFillColor(RandomUtils::randomColor());
	ball.setOrigin(sf::Vector2f(radius, radius));
	ball.setPosition(position);

	mass = MathUtils::computeMass(radius);
	color = ball.getFillColor();
	points = static_cast<int>(
		Config::Ball::MIN_RADIUS / radius * Config::Ball::BASE_POINTS);
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

float Ball::getRadius() const
{
	return radius;
}

float Ball::getMass() const
{
	return mass;
}

const sf::Vector2f& Ball::getVelocity() const
{
	return velocity;
}

sf::Vector2f& Ball::getVelocity()
{
	return velocity;
}

const sf::Vector2f& Ball::getPosition() const
{
	return position;
}

sf::Vector2f& Ball::getPosition()
{
	return position;
}

int Ball::getPoints() const
{
	return points;
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

	int whiteState = static_cast<int>(
		flashingTime * Config::Ball::BLINKING_SPEED);

	ball.setFillColor((whiteState & 1) == 0 ? sf::Color::White : color);

	if (flashingTime <= 0.f)
	{
		isFlashing = false;
		ball.setFillColor(color);
	}
}