#include "Player.h"
#include "MathUtils.h"
#include "PhysicsUtils.h"

using namespace sf;
using namespace MathUtils;
using namespace PhysicsUtils;

const float RECTANGLE_WIDTH = 60.f;
const float RECTANGLE_HEIGHT = 30.f;

const float FOLLOW_SMOOTHING = 0.7f;

Player::Player(const RenderWindow& window)
{
    rectangle.setSize(Vector2f(RECTANGLE_WIDTH,
        RECTANGLE_HEIGHT));
    rectangle.setOrigin(rectangle.getSize() / 2.f);
    rectangle.setFillColor(Color::Red);
    rectangle.setPosition(
        static_cast<Vector2f>(window.getSize()) / 2.f);
}

void Player::rotate(float angle)
{
    rectangle.rotate(degrees(angle));
}

void Player::update(const RenderWindow& window)
{
    Vector2i mousePosition = Mouse::getPosition(window);
    Vector2f worldRectCenter = rectangle.getPosition();
    Vector2i worldCenterPixels = window.mapCoordsToPixel(worldRectCenter);

    Vector2f difference = static_cast<Vector2f>
        (mousePosition - worldCenterPixels);

    rectangle.move(difference * FOLLOW_SMOOTHING);
    Mouse::setPosition(worldCenterPixels, window);

    Vector2f rectangleHalfSize = rectangle.getSize() / 2.f;
    worldRectCenter = rectangle.getPosition();

    clampRectangleToWindow(worldRectCenter, rectangleHalfSize, window.getSize());

    rectangle.setPosition(worldRectCenter);
}

void Player::draw(RenderWindow& window) const
{
    window.draw(rectangle);
}

const RectangleShape& Player::getRectangle() const
{
	return rectangle;
}