#include "GamePlayScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

constexpr float DEGREE = 90.f;

GamePlayScreen::GamePlayScreen(Game& game, RenderWindow& window) :
	Screen(game, window),
	player(window),
	ballManager(window),
	paused(false),
	survivalClock(),
	survivalTimeText(Text(game.getFont(), "", Screen::BODY_TEXT_SIZE))
{
	this->window.setMouseCursorVisible(false);
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
	
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		player.rotate(DEGREE);
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

