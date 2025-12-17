#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"

using namespace sf;
using namespace std;

GamePlayScreen::GamePlayScreen(Game& game, RenderWindow& window) :
	Screen(game, window),
	gameWorld(game, window.getSize()),
	paused(false),
	survivalClock(),
	survivalTimeText(Text(game.getFont(), "", BODY_TEXT_SIZE))
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

	Vector2f mousePosition =
		window.mapPixelToCoords(Mouse::getPosition(window));
	const Vector2u& windowSize = window.getSize();

	gameWorld.update(deltaTime, windowSize, mousePosition);

	if (gameWorld.isGameOver())
	{
		game.switchScreen<GameOverScreen>(window, survivalTime);
		return;
	}
}

void GamePlayScreen::render(RenderWindow& window)
{
	gameWorld.render(window);
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
