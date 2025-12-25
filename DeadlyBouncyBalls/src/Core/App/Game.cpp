#include "Core/App/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/Tutorial/TutorialScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"

using namespace sf;
using namespace std;

const VideoMode& DESKTOP_MODE = VideoMode::getDesktopMode();

Game::Game() :
	window(VideoMode(DESKTOP_MODE), "Deadly Bouncy Balls",
		Style::None)
{
	assets.loadFont();
	assets.loadAssets();
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

const GameAssets& Game::getAssets() const
{
	return assets;
}