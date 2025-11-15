#include "Player.h"

using namespace sf;

const int INITIAL_RECTANGLE_WIDTH = 50;
const int INITIAL_RECTANGLE_HEIGHT = 25;

Player::Player(const RenderWindow& window)
{
    rectangle.setSize(Vector2f(INITIAL_RECTANGLE_WIDTH, 
        INITIAL_RECTANGLE_HEIGHT));
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
    Vector2f rectangleHalfSize = rectangle.getSize() / 2.f;

    Vector2i worldCenterPixels = window.
        mapCoordsToPixel(worldRectCenter);

    Vector2f difference = static_cast<Vector2f>
        (mousePosition - worldCenterPixels);

    rectangle.move(difference * 0.7f);

    Mouse::setPosition(worldCenterPixels, window);
}

void Player::draw(RenderWindow& window) const
{
    window.draw(rectangle);
}

const RectangleShape& Player::getRectangle() const
{
	return rectangle;
}