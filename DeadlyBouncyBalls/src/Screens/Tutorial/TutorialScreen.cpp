#include "Core/App/Game.h"
#include "Screens/Tutorial/TutorialScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"

TutorialScreen::TutorialScreen(Game& game) :
	Screen(game)
{
	tutorialOverlay = std::make_unique<TutorialOverlay>(game);
}

void TutorialScreen::handleEvent(const sf::Event& event)
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

void TutorialScreen::update(
	float deltaTime,
	const Input& Input)
{
	if (tutorialOverlay)
		tutorialOverlay->update(deltaTime, Input);
}

void TutorialScreen::render()
{
	auto& renderer = game.getRenderer();

	if (tutorialOverlay)
		tutorialOverlay->render();
}