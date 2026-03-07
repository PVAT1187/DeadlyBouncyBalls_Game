#include "Core/App/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/Tutorial/TutorialScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"

using namespace sf;
using namespace std;

Game::Game()
{
	assets.load();
	switchScreen<GameStartScreen>();
}

void Game::run()
{
	Clock clock;

	while (renderer.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		while (const optional event = renderer.pollEvent())
		{
			if (event->is<Event::Closed>())
				renderer.close();
			
			currentScreen->handleEvent(*event);
		}

		InputState inputState = inputSystem.collect(renderer);
		currentScreen->update(deltaTime, inputState);

		renderer.clear();
		currentScreen->render();
		renderer.display();
	}
}

const GameAssets& Game::getAssets() const
{
	return assets;
}

Renderer& Game::getRenderer()
{
	return renderer;
}

const InputSystem& Game::getInputSystem() const 
{
	return inputSystem;
}