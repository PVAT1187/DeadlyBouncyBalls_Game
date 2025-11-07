#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace sf;
using namespace std;

const int RECTANGLE_WIDTH = 50;
const int RECTANGLE_HEIGHT = 25;

enum class GameState { Playing, GameOver };

int main()
{
    VideoMode desktopMode = VideoMode::getDesktopMode();

    RenderWindow window(VideoMode(desktopMode),
        "Deadly Bouncy Balls", Style::None);
    window.setPosition(Vector2i(0, 0));
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);

    Font defaultFont;

    RectangleShape rectangle(Vector2f
        (RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    rectangle.setOrigin(rectangle.getSize() / 2.f);
    rectangle.setFillColor(Color::Red);
    rectangle.setPosition(static_cast<Vector2f>
        (window.getSize()) / 2.f);

    CircleShape circle(20.f);
	float radius = circle.getRadius();
	circle.setFillColor(Color::Blue);
    circle.setPosition(static_cast<Vector2f>
		(window.getSize()) / 4.f);
	Vector2f circleVelocityVector(200.f, 150.f);

	Clock clock;

	GameState currentGameState = GameState::Playing;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            if (event->is<Event::MouseButtonPressed>() &&
                event->getIf<Event::MouseButtonPressed>()->button
                == Mouse::Button::Left)
            {
                rectangle.rotate(degrees(90));
            }
        }

        Vector2i mousePosition = Mouse::getPosition(window);
        Vector2f worldRectCenter = rectangle.getPosition();
		Vector2f rectangleHalfSize = rectangle.getSize() / 2.f;

        Vector2i worldCenterPixels = window.
            mapCoordsToPixel(worldRectCenter);

        Vector2f difference = static_cast<Vector2f>
            (mousePosition - worldCenterPixels);

        rectangle.move(difference * 0.7f);

        Mouse::setPosition(worldCenterPixels, window);

		float deltaTime = clock.restart().asSeconds();
		circle.move(circleVelocityVector * deltaTime);

		Vector2f circlePosition = circle.getPosition(); // center position
        float circleLeftEdge = circlePosition.x - radius;
        float circleRightEdge = circlePosition.x + radius;
        float circleTopEdge = circlePosition.y - radius;
        float circleBottomEdge = circlePosition.y + radius;

        if (circleLeftEdge <= 0 || 
            circleRightEdge >= window.getSize().x)
        {
			circleVelocityVector.x = -circleVelocityVector.x;
        }
        if (circleTopEdge <= 0 || 
            circleBottomEdge >= window.getSize().y)
        {
			circleVelocityVector.y = -circleVelocityVector.y;
        }

		Vector2f closetPoint;
		closetPoint.x = clamp(circlePosition.x, 
            worldRectCenter.x - rectangleHalfSize.x,
			worldRectCenter.x + rectangleHalfSize.x);
        closetPoint.y = clamp(circlePosition.y, 
			worldRectCenter.y - rectangleHalfSize.y,
			worldRectCenter.y + rectangleHalfSize.y);

		Vector2f differenceVector = circlePosition - closetPoint;
        float distanceSquared = 
            differenceVector.x * differenceVector.x +
			differenceVector.y * differenceVector.y;

		const float EPSILON = 0.0001f;
        if ((distanceSquared - radius * radius) < EPSILON)
        {
            currentGameState = GameState::GameOver;
        }

        if (currentGameState == GameState::GameOver)
        {
			cout << "Game Over!" << endl;
            Text gameOverText(defaultFont, "GAME OVER", 30);
			gameOverText.setFillColor(Color::White);
            gameOverText.setPosition(
				static_cast<Vector2f>(window.getSize()) / 2.f);
			window.draw(gameOverText);
        }

        window.clear();
        window.draw(rectangle);
		window.draw(circle);
        window.display();
    }
}