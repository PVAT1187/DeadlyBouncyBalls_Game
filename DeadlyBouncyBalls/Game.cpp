#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

const sf::VideoMode& DESKTOP_MODE = sf::VideoMode::getDesktopMode();

Game::Game() :
	window(VideoMode(DESKTOP_MODE), "Deadly Bouncy Balls", Style::None),
	player(window),
	ball(window),
	isGameOver(false),
	font(),
	gameOverText(Text(font, "GAME OVER", 60))
{
	window.setPosition(Vector2i(0, 0));
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);

	if (!font.openFromFile("C:/Users/pvat2/source/Personal Projects/DeadlyBouncyBalls/assets/fonts/arial.ttf"))
	{
		cerr << "Failed to load font!" << endl;
	}

	gameOverText.setFont(font);
	gameOverText.setFillColor(Color::White);

	FloatRect textBounds = gameOverText.getLocalBounds();
	gameOverText.setOrigin(
		Vector2f(textBounds.size.x, textBounds.size.y) / 2.f);
	gameOverText.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
}

void Game::run()
{
	Clock clock;
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		processEvents();

		if (!isGameOver)
		{
			update(deltaTime);
		}
		
		render();
	}
}

void Game::processEvents()
{
	while (const optional event = window.pollEvent())
	{
		if (event->is<Event::Closed>())
			window.close();
		if (event->is<Event::MouseButtonPressed>() &&
			event->getIf<Event::MouseButtonPressed>()->button
			== Mouse::Button::Left)
		{
			player.rotate(90.f);
		}
	}
}

void Game::update(float deltaTime)
{
	ball.update(deltaTime, window);
	if (ball.isCollidingWithPlayer(player))
	{
		isGameOver = true;
	}
	player.update(window);
}

void Game::render()
{
	window.clear();

	player.draw(window);
	ball.draw(window);

	if (isGameOver)
	{
		window.draw(gameOverText);
	}

	window.display();
}