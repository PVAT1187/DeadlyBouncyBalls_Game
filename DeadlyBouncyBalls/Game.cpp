#include "Game.h"
#include "GamePlayScreen.h"
#include "GameOverScreen.h"

using namespace sf;
using namespace std;

const VideoMode& DESKTOP_MODE = VideoMode::getDesktopMode();

Game::Game() :
	window(VideoMode(DESKTOP_MODE), "Deadly Bouncy Balls",
		Style::None)
{
	switchToGamePlayScreen();
}

void Game::run()
{
	Clock clock;

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();

			currentScreen->handleEvent(event);
		}

		currentScreen->update(deltaTime);

		window.clear();
		currentScreen->render(window);
		window.display();
	}
}

void Game::switchToGamePlayScreen()
{
	currentScreen = make_unique<GamePlayScreen>(*this, window);
}

void Game::switchToGameOverScreen(float finalSurvivalTime)
{
	currentScreen = make_unique<GameOverScreen>(*this, window,
		finalSurvivalTime);
}