#include "Game.h"
#include "GameStartScreen.h"
#include "GamePlayScreen.h"
#include "GameOverScreen.h"

#include <iostream>

using namespace sf;
using namespace std;

const VideoMode& DESKTOP_MODE = VideoMode::getDesktopMode();

Game::Game() :
	window(VideoMode(DESKTOP_MODE), "Deadly Bouncy Balls",
		Style::None)
{
	initFont();
	switchToGameStartScreen();
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

			currentScreen->handleEvent(*event);
		}

		currentScreen->update(deltaTime);

		window.clear();
		currentScreen->render(window);
		window.display();
	}
}

void Game::switchToGameStartScreen()
{
	currentScreen = make_unique<GameStartScreen>(*this, window);
}

void Game::switchToGamePlayScreen()
{
	currentScreen = make_unique<GamePlayScreen>(*this, window);
}

void Game::switchToGameOverScreen(float survivalTime)
{
	currentScreen = make_unique<GameOverScreen>(*this, window,
		survivalTime);
}

void Game::initFont()
{
	if (!font.openFromFile("C:/Users/pvat2/source/Personal Projects/DeadlyBouncyBalls/assets/fonts/arial.ttf"))
	{
		cerr << "Failed to load font!" << endl;
	}
}

Font& Game::getFont() 
{ 
	return font; 
}