#include "Core/Game.h"
#include "Screens/GameStartScreen.h"
#include "Screens/GameDemoScreen.h"
#include "Screens/GamePlayScreen.h"
#include "Screens/GameOverScreen.h"

#include <iostream>

using namespace sf;
using namespace std;

const VideoMode& DESKTOP_MODE = VideoMode::getDesktopMode();

Game::Game() :
	window(VideoMode(DESKTOP_MODE), "Deadly Bouncy Balls",
		Style::None)
{
	initFont();
	initTexture();
	switchScreen<GameStartScreen>(window);
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

const Font& Game::getFont() const
{ 
	return font; 
}

const Texture& Game::getPlayerTexture() const
{
	return playerTexture;
}

const Texture& Game::getAimingIconTexture() const
{
	return aimingIconTexture;
}

void Game::initFont()
{
	if (!font.openFromFile("assets/fonts/arial.ttf"))
		throw runtime_error("Failed to load font!");
}

void Game::initTexture()
{
	if (!playerTexture.loadFromFile("assets/PNG/Player/player_sprite.png"))
		throw runtime_error("Failed to load player texture!");

	if (!aimingIconTexture.loadFromFile("assets/PNG/Icons/crosshair.png"))
		throw runtime_error("Failed to load aiming icon texture!");
}