#include "GamePlayScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

const float DEGREE = 90.f;

GamePlayScreen::GamePlayScreen(Game& game, RenderWindow& window) :
	Screen(game, window),
	player(window),
	ballManager(window),
	paused(false),
	survivalClock(),
	pausedDuration(Time::Zero),
	survivalTimeText(Text(game.getFont(), "", Screen::BODY_TEXT_SIZE))
{
	this->window.setMouseCursorVisible(false);
	initSurvivalTimeText();
	
	survivalClock.restart();

	pauseOverlay = make_unique<PauseMenuOverlay>(game, window);
}

void GamePlayScreen::handleEvent(const Event& event)
{
	if (event.is<Event::KeyPressed>() &&
		event.getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)
	{
		paused = !paused;

		if (paused)
		{
			window.setMouseCursorVisible(true);
			pauseOverlay->activate();
			pausedAt = survivalClock.getElapsedTime();
		}
		else
		{
			window.setMouseCursorVisible(false);
			pauseOverlay->deactivate();
			pausedDuration += survivalClock.getElapsedTime() - pausedAt;
		}

		return;
	}

	if (paused)
	{
		pauseOverlay->handleEvent(event);
		return;
	}
	
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		player.rotate(DEGREE);
	}
}

void GamePlayScreen::update(float deltaTime)
{	
	if (paused)
		return;
	
	float survivalTime = (survivalClock.getElapsedTime() - pausedDuration).asSeconds();
	survivalTimeText.setString("Survival Time: " +
		to_string(survivalTime) + "s");

	player.update(window);
	ballManager.update(deltaTime, window);

	if (ballManager.isGameOver(player))
	{
		game.switchToGameOverScreen(survivalTime);
		return;
	}
}

void GamePlayScreen::render(RenderWindow& window)
{
	player.draw(window);
	ballManager.draw(window);
	window.draw(survivalTimeText);

	if (paused)
		pauseOverlay->render(window);
}

void GamePlayScreen::initSurvivalTimeText()
{
	survivalTimeText.setFillColor(Color::White);

	FloatRect survivalTimeTextBounds = survivalTimeText.getLocalBounds();
	survivalTimeText.setOrigin(survivalTimeTextBounds.size / 2.f);
	survivalTimeText.setPosition(Vector2f(0, 0));
}

