#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"

using namespace sf;
using namespace std;

GamePlayScreen::GamePlayScreen(Game& game) :
	Screen(game),
	gameWorld(game.getAssets(), game.getRenderer().getWindowSize()),
	survivalTimeText(Text(game.getAssets().getFont(), "", BODY_TEXT_SIZE)),
	survivalClock()
{
	game.getRenderer().showCursor(false);
	initSurvivalTimeText();
	survivalClock.restart();
}

void GamePlayScreen::handleEvent(const Event& event)
{
	if (event.is<Event::KeyPressed>() &&
		event.getIf<Event::KeyPressed>()->code == 
		Keyboard::Key::Escape)
	{
		if (!pauseOverlay)
		{
			pauseOverlay = make_unique<PauseMenuOverlay>(game);
			game.getRenderer().showCursor(true);
		}
		else
		{
			pauseOverlay.reset();
			game.getRenderer().showCursor(false);
		}
	}

	if (pauseOverlay)
	{
		pauseOverlay->handleEvent(event);
		
		if (pauseOverlay->hasSelectedOption())
		{
			switch (pauseOverlay->getSelectedOption())
			{
				case PauseMenuOption::RESUME:
					pauseOverlay.reset();
					game.getRenderer().showCursor(false);
					break;
				case PauseMenuOption::MAIN_MENU:
					game.switchScreen<GameStartScreen>();
					break;
			}
		}
	}
}

void GamePlayScreen::update(float deltaTime,
	const InputState& inputState)
{	
	if (pauseOverlay)
	{
		pauseOverlay->update(deltaTime, inputState);
		return;
	}
	
	float survivalTime = survivalClock.getElapsedTime().asSeconds();
	updateSurvivalTimeText(survivalTime);
	
	gameWorld.update(deltaTime, inputState);
	if (gameWorld.isGameOver())
	{
		game.switchScreen<GameOverScreen>(survivalTime);
		return;
	}
}

void GamePlayScreen::render()
{
	auto& renderer = game.getRenderer();
	
	gameWorld.render(renderer);
	renderer.draw(survivalTimeText);

	if (pauseOverlay)
		pauseOverlay->render();
}

void GamePlayScreen::initSurvivalTimeText()
{
	survivalTimeText.setFillColor(Color::White);

	FloatRect survivalTimeTextBounds = survivalTimeText.getLocalBounds();
	survivalTimeText.setOrigin(survivalTimeTextBounds.size / 2.f);
	survivalTimeText.setPosition(Vector2f(0, 0));
}

void GamePlayScreen::updateSurvivalTimeText(float survivalTime)
{
	survivalTimeText.setString("Survival Time: " +
		to_string(survivalTime) + "s");
}
