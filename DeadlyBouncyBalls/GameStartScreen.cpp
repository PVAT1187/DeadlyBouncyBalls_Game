#include "GameStartScreen.h"
#include "Game.h"

using namespace sf;

const unsigned int GAME_TITLE_TEXT_SIZE = 100;
const unsigned int BUTTON_SIZE = 50;
const float TITLE_BUTTON_SPACING = 150.f;
const float BUTTON_SPACING = 80.f;

GameStartScreen::GameStartScreen(Game& game, RenderWindow& window) :
	Screen(game),
	game(game),
	window(window),
	gameTitleText(Text(game.getFont(), "DEADLY BOUNCY BALLS", GAME_TITLE_TEXT_SIZE)),
	playButton("PLAY", game.getFont(), BUTTON_SIZE, { 0, 0 }),
	quitButton("QUIT", game.getFont(), BUTTON_SIZE, { 0, 0 })
{
	initGameTilteText();
	updateButtonPositon();
}

void GameStartScreen::handleEvent(const Event& event) {}

void GameStartScreen::update(float deltaTime) 
{
	playButton.update(window);
	quitButton.update(window);

	if (playButton.isClicked(window))
	{
		game.switchToGamePlayScreen();
	}
	else if (quitButton.isClicked(window))
	{
		window.close();
	}
}

void GameStartScreen::render(RenderWindow& window)
{
	window.draw(gameTitleText);
	playButton.draw(window);
	quitButton.draw(window);
}

void GameStartScreen::initGameTilteText()
{
	gameTitleText.setFillColor(Color::White);

	FloatRect gameTitleTextBounds = gameTitleText.getLocalBounds();
	gameTitleText.setOrigin(gameTitleTextBounds.size / 2.f);
	gameTitleText.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
}


void GameStartScreen::updateButtonPositon()
{
	float startY = gameTitleText.getPosition().y + TITLE_BUTTON_SPACING;

	playButton.setPosition({ window.getSize().x / 2.f, startY });
	quitButton.setPosition({ window.getSize().x / 2.f, startY + BUTTON_SPACING });
}