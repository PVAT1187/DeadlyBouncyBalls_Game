#include "Screens/GameDemo/GameDemoScreen.h"

using namespace sf;
using namespace std;

GameDemoScreen::GameDemoScreen(Game& game, RenderWindow& window) :
	Screen(game, window),
	ballManager(window.getSize()),
	instructionShown(true)
{
	instructionOverlay = make_unique<InstructionOverlay>(game, window);
}

void GameDemoScreen::handleEvent(const Event& event)
{
	if (instructionShown)
	{
		instructionOverlay->handleEvent(event);
		return;
	}
}

void GameDemoScreen::update(float deltaTime)
{
	if (instructionShown && instructionOverlay)
	{
		instructionOverlay->update();
	}

	const Vector2u& windowSize = window.getSize();
	ballManager.update(deltaTime, windowSize);
}

void GameDemoScreen::render(RenderWindow& window)
{
	ballManager.draw(window);

	if (instructionShown)
		instructionOverlay->render(window);
}