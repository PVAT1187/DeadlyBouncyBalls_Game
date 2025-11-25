#include "GameStartScreen.h"
#include "Game.h"

using namespace sf;

const int GAME_TITLE_TEXT_SIZE = 100;
const int GAME_INSTRUCTION_TEXT_SIZE = 25;

GameStartScreen::GameStartScreen(Game& game, RenderWindow& window) :
	Screen(game),
	game(game),
	window(window),
	gameTitleText(Text(game.getFont(), "DEADLY BOUNCY BALLS", GAME_TITLE_TEXT_SIZE)),
	gameInstructionText(Text(game.getFont(), "", GAME_INSTRUCTION_TEXT_SIZE))
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