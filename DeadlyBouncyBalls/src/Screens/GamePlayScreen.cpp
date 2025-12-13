#include "Screens/GamePlayScreen.h"
#include "Screens/GameOverScreen.h"
#include "Core/Game.h"

#include <iostream>

using namespace sf;
using namespace std;

GamePlayScreen::GamePlayScreen(Game& game, RenderWindow& window) :
	Screen(game, window),
	player(game.getPlayerTexture(), game.getAimingIconTexture()),
	ballManager(window.getSize()),
	paused(false),
	survivalClock(),
	survivalTimeText(Text(game.getFont(), "", BODY_TEXT_SIZE))
{
	this->window.setMouseCursorVisible(false);
	
	positionPlayer();
	initSurvivalTimeText();
	
	survivalClock.restart();

	pauseOverlay = make_unique<PauseMenuOverlay>(*this, game, window);
}

void GamePlayScreen::handleEvent(const Event& event)
{
	if (event.is<Event::KeyPressed>() &&
		event.getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)
	{
		paused = !paused;
		window.setMouseCursorVisible(paused);
		return;
	}

	if (paused)
	{
		pauseOverlay->handleEvent(event);
		return;
	}
}

void GamePlayScreen::update(float deltaTime)
{	
	if (paused)
	{
		pauseOverlay->update();
		return;
	}
	
	float survivalTime = survivalClock.getElapsedTime().asSeconds();
	updateSurvivalTimeText(survivalTime);

	const Vector2u& windowSize = window.getSize();
	Vector2f mousePosition = 
		window.mapPixelToCoords(Mouse::getPosition(window));

	player.setMouseTarget(mousePosition);
	player.update(deltaTime, windowSize);
	ballManager.update(deltaTime, windowSize);

	if (ballManager.isGameOver(player))
	{
		game.switchScreen<GameOverScreen>(window, survivalTime);
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

void GamePlayScreen::unpause()
{
	paused = false;
	window.setMouseCursorVisible(false);
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

void GamePlayScreen::positionPlayer()
{
	Vector2u windowSize = window.getSize();
	player.getSprite().setPosition(
		Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));
}

