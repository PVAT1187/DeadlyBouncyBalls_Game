#include "GameStartScreen.h"
#include "Game.h"

using namespace sf;

GameStartScreen::GameStartScreen(Game& game, RenderWindow& window) :
	Screen(game),
	game(game),
	window(window),
	gameTitleText(Text(game.getFont(), "DEADLY BOUNCY BALLS", 100)),
	gameInstructionText(Text(game.getFont(), "", 25))
{
	initGameTilteText();
	initGameInstructionText();
}

void GameStartScreen::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>())
	{
		game.switchToGamePlayScreen();
	}
}

void GameStartScreen::update(float deltaTime) {}

void GameStartScreen::render(RenderWindow& window)
{
	window.draw(gameTitleText);
	window.draw(gameInstructionText);
}

void GameStartScreen::initGameTilteText()
{
	gameTitleText.setFillColor(Color::White);

	FloatRect gameTitleTextBounds = gameTitleText.getLocalBounds();
	gameTitleText.setOrigin(gameTitleTextBounds.size / 2.f);
	gameTitleText.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
}

void GameStartScreen::initGameInstructionText()
{
	
}