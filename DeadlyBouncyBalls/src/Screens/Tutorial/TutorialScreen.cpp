#include "Core/App/Game.h"
#include "Screens/Tutorial/TutorialScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"

using namespace sf;
using namespace std;

TutorialScreen::TutorialScreen(Game& game) :
	Screen(game),
	worldBounds(game.getRenderer().getWindowSize()),
	boundarySystem(worldBounds),
	ballManager(worldBounds)
{
	tutorialOverlay = make_unique<TutorialOverlay>(game);
}

void TutorialScreen::handleEvent(const Event& event) 
{
	if (tutorialOverlay)
	{
		tutorialOverlay->handleEvent(event);

		if (tutorialOverlay->isFinished())
		{
			tutorialOverlay.reset();
			game.switchScreen<GamePlayScreen>();
		}

		return;
	}
}

void TutorialScreen::update(float deltaTime,
	const InputState& inputState)
{
	if (tutorialOverlay)
		tutorialOverlay->update(deltaTime, inputState);

	ballManager.update(deltaTime);
	boundarySystem.apply(ballManager);
}

void TutorialScreen::render()
{
	auto& renderer = game.getRenderer();
	
	ballManager.draw(renderer);

	if (tutorialOverlay)
		tutorialOverlay->render();
}