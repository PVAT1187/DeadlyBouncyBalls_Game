#include "Core/App/Game.h"
#include "Core/Input/Input.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/Tutorial/TutorialScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"

Game::Game()
{
	assets.load();
	switchScreen<GameStartScreen>();
}

void Game::run()
{
	sf::Clock clock;

	while (renderer.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = renderer.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				renderer.close();
			
			currentScreen->handleEvent(*event);
		}

		Input input = inputCollector.collect(renderer);
		currentScreen->update(deltaTime, input);

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

const InputCollector& Game::getInputCollector() const
{
	return inputCollector;
}