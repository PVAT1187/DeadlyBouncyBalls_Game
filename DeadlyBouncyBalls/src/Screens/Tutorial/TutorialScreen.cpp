#include "Screens/Tutorial/TutorialScreen.h"

using namespace sf;
using namespace std;

TutorialScreen::TutorialScreen(Game& game, RenderWindow& window) :
	Screen(game, window),
	ballManager(window.getSize()),
	instructionShown(true)
{
	tutorialOverlay = make_unique<TutorialOverlay>(game, window);
}

void TutorialScreen::handleEvent(const Event& event) 
{
	if (instructionShown)
	{
		tutorialOverlay->handleEvent(event);
		return;
	}
}

void TutorialScreen::update(float deltaTime)
{
	if (instructionShown && tutorialOverlay)
	{
		tutorialOverlay->update();
	}

	const Vector2u& windowSize = window.getSize();
	ballManager.update(deltaTime, windowSize);
}

void TutorialScreen::render(RenderWindow& window)
{
	ballManager.draw(window);

	if (instructionShown)
		tutorialOverlay->render(window);
}