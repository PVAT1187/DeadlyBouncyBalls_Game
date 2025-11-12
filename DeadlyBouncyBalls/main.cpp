#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameState.h"
#include "Player.h"
#include "Ball.h"

using namespace sf;
using namespace std;

int main()
{
    

    RenderWindow window(VideoMode(desktopMode),
        "Deadly Bouncy Balls", Style::None);
    window.setPosition(Vector2i(0, 0));
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);

    Font defaultFont("C:/Users/pvat2/source/Personal Projects/DeadlyBouncyBalls/assets/fonts/arial.ttf");

	Player player(window);

    Ball ball(window);

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
                player.rotate(degrees(90));
            }
        }

        window.clear();
        if (currentGameState == GameState::Playing)
        {
            player.update(window);

            float deltaTime = clock.restart().asSeconds();
			ball.update(deltaTime, window);

            if (ball.isCollidingWithPlayer(player))
            {
                currentGameState = GameState::GameOver;
            }
        }
        
		player.draw(window);
		ball.draw(window);

        if (currentGameState == GameState::GameOver)
        {
            window.setMouseCursorVisible(true);
            
            Text gameOverText(defaultFont, "GAME OVER", 60);
            gameOverText.setFillColor(Color::White);

			FloatRect textBounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin(
                Vector2f(textBounds.size.x, textBounds.size.y) / 2.f);
            gameOverText.setPosition(
                static_cast<Vector2f>(window.getSize()) / 2.f);

            window.draw(gameOverText);
        }

        window.display();
    }
}